#include "packet.h"

int EtherHeader::type() const {
    return ntohs(ether_type);
}

int IpHeader::length() const {
    return (version_ihl & 0x0F) << 2;
}

int IpHeader::total_length() const {
    return ntohs(packet_length);
}

int TcpHeader::length() const {
    return (hl_rb_flags & 0x00F0) >> 2;
}

int TcpHeader::sport() const {
    return ntohs(src);
}

int TcpHeader::dport() const {
    return ntohs(dst);
}

void print_tcp_data(int packet_length, int tcp_index, const uint8_t *packet) {
    int diff = packet_length - tcp_index;
    if (diff > 0) {
        if (diff > 10) diff = 10;
        std::cout << "TCP Data: ";
        for (int i = 0; i < diff; i++) std::cout << std::hex << int(packet[tcp_index + i]) << " ";
        std::cout << std::endl;
    }
}

std::ostream &operator<<(std::ostream &o, const EtherHeader& eth) {
    o << "<Ether ";
    o << "dst=" << eth.dst << " ";
    o << "src=" << eth.src << " ";
    o << "type=0x" << std::hex << eth.type() << " ";
    o << "|>";
    return o;
}

std::ostream &operator<<(std::ostream &o, const IpHeader& ip) {
    o << "<IP ";
    o << "src=" << ip.sip << " ";
    o << "srt=" << ip.dip << " ";
    o << "ttl=" << std::dec << int(ip.ttl);
    o << "|>";
    return o;
}

std::ostream &operator<<(std::ostream &o, const TcpHeader& tcp)  {
    o << "<TCP ";
    o << "sport=" << tcp.sport() << " ";
    o << "dport=" << tcp.dport() << " ";
    o << "|>";
    return o;
}