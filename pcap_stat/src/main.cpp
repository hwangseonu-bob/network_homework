#include <pcap.h>
#include <iostream>
#include "../includes/network/statistics.h"

using namespace std;
using namespace network;

void usage(const string& cmd) {
    cout << "usage: " << cmd << " "
         << "<pcap file>" << endl;
    cout << "example: " << cmd << " "
         << "capture.pcap" << endl;
}

void print_mac_address_statistics(const string& filename) {
    PacketCapture capture(filename);

    EnpointsStatistic<MacAddress> e;
    ConversationsStatistic<MacAddress> c;

    bytes pk;
    while ((pk = capture.next()).size() > 0) {
        Ipv4Packet ipv4(pk);

        e.add(ipv4.eth.src, pk, true);
        e.add(ipv4.eth.dst, pk, false);
        c.add(ipv4.eth.src, ipv4.eth.dst, pk);
    }
    cout << e << endl;
    cout << c << endl;
}

void print_ip_address_statistics(const string& filename) {
    PacketCapture capture(filename);

    EnpointsStatistic<Ipv4Address> e;
    ConversationsStatistic<Ipv4Address> c;

    bytes pk;
    while ((pk = capture.next()).size() > 0) {
        Ipv4Packet ipv4(pk);

        e.add(ipv4.ip.src, pk, true);
        e.add(ipv4.ip.dst, pk, false);
        c.add(ipv4.ip.src, ipv4.ip.dst, pk);
    }
    cout << e << endl;
    cout << c << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return -1;
    }

    int select;

    cout << "1. Mac Address Statistics" << endl;
    cout << "2. Ip Address Statistics" << endl;
    cout << "Select: ";

    cin >> select;

    switch (select) {
        case 1:
            print_mac_address_statistics(argv[1]);
            break;
        case 2:
            print_ip_address_statistics(argv[1]);
            break;
    }

    return 0;
}