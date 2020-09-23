#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>

#include "packet.h"

#define MAX_PACKET_SIZE 8192

using namespace std;

void usage(char *cmd) {
    cerr << "syntax: " << cmd << " <interface>" << endl;
    cerr << "example: " << cmd << " wlan0" << endl;
}

void handle_packet(pcap_pkthdr *header, const uint8_t *packet) {
    auto eth = reinterpret_cast<const EtherHeader *>(packet);
    if (eth->type() == ETHERTYPE_IP) {
        auto ip = reinterpret_cast<const IpHeader *>(packet + sizeof(EtherHeader));
        if (ip->protocol == IPPROTO_TCP) {
            auto tcp = reinterpret_cast<const TcpHeader *>(packet + sizeof(EtherHeader) + ip->length());
            cout << string(50, '=') << endl;
            cout << *eth << endl;
            cout << *ip << endl;
            cout << *tcp << endl;
            print_tcp_data(sizeof(EtherHeader) + ip->total_length(),
                    sizeof(EtherHeader) + ip->length() + tcp->length(), packet);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    pcap_pkthdr *header;
    const uint8_t *packet;
    char err_buf[PCAP_ERRBUF_SIZE];
    int res = 0;
    pcap_t *handle = nullptr;

    cout << "Opening device " << argv[1] << endl;
    handle = pcap_open_live(argv[1], MAX_PACKET_SIZE, 0, 512, err_buf);

    if (handle == nullptr) {
        cerr << "couldn't open device " << argv[1] << ":" << err_buf << endl;
        return EXIT_FAILURE;
    }

    while ((res = pcap_next_ex(handle, &header, &packet)) >= 0) {
        if (res == 0) continue;
        handle_packet(header, packet);
    }

    pcap_close(handle);
    return EXIT_SUCCESS;
}