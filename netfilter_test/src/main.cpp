#include <iostream>
#include <netinet/in.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/tcp.h>

using namespace std;

string target;

bool find_url(const uint8_t* buf) {
    auto *iph = (iphdr*) buf;
    auto *tcph = (tcphdr*) (buf + iph->ihl * 4);
    int header_size = iph->ihl * 4 + tcph->doff * 4;

    char* host = strstr((char*)buf + header_size, "Host: ");
    if (host != nullptr) {
        size_t len = 0;
        for (len = 0; host[len + 6] != '\r'; len++);
        string url = string(host + 6, len);
        if (url == target) return true;
    }
    return false;
}

static int handle(nfq_q_handle *qh, nfgenmsg *nfmsg, nfq_data *nfa, void *data) {
    struct nfqnl_msg_packet_hdr *ph;
    ph = nfq_get_msg_packet_hdr(nfa);
    uint32_t id = 0;
    if (ph) {
        id = ntohl(ph->packet_id);
    }
    uint8_t *pk;
    int ret = nfq_get_payload(nfa, &pk);
    if (find_url(pk)) {
        cout << "blocked site" << endl;
        return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
    } else {
        return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << argv[0] << " <block site>" << endl;
        return -1;
    }
    target = string(argv[1]);
    nfq_handle *h;
    nfq_q_handle *qh;
    nfnl_handle *nh;

    int fd, rv;
    char buf[4096] __attribute__ ((aligned));

    cout << "opening library handle" << endl;
    if (!(h = nfq_open())) {
        cerr << "error during nfq_open()" << endl;
        exit(1);
    }

    cout << "unbinding existing nf_queue for AF_INET (if any)" << endl;
    if (nfq_unbind_pf(h, AF_INET) < 0) {
        cerr << "error during nfq_unbind_pf()" << endl;
        exit(1);
    }

    cout << "binding nfnetlink_queue as nf_queue handler for AF_INET" << endl;
    if (nfq_bind_pf(h, AF_INET) < 0) {
        cerr << "error during nfq_bind_pf()" << endl;
        exit(1);
    }

    cout << "binding this socket to queue '0'" << endl;
    if (!(qh = nfq_create_queue(h, 0, &handle, NULL))) {
        cerr << "error during nfq_create_queue()" << endl;
        exit(1);
    }

    cout << "setting copy_packet mode" << endl;
    if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
        cerr << "can't set packet_copy mode" << endl;
        exit(1);
    }

    fd = nfq_fd(h);
    while (true) {
        if ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
//            cout << "pk received" << endl;
            nfq_handle_packet(h, buf, rv);
            continue;
        }

        if (rv < 0 && errno == ENOBUFS) {
            cout << "losing packets!" << endl;
            continue;
        }
        perror("receive failed");
        break;
    }

    cout << "unbinding from queue 0" << endl;
    nfq_destroy_queue(qh);

#ifdef INSANE
    /* normally, applications SHOULD NOT issue this command, since
     * it detaches other programs/sockets from AF_INET, too ! */
    cout << "unbinding from AF_INET" << endl;
    nfq_unbind_pf(h, AF_INET);
#endif

    cout << "closing library handle" << endl;
    nfq_close(h);
    exit(0);
}