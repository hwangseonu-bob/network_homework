#ifndef __PCAP_STAT_IPV4_PACKET__
#define __PCAP_STAT_IPV4_PACKET__

#include "ether_header.h"
#include "ipv4_header.h"

namespace network {
    class Ipv4Packet {
       public:
        EtherHeader eth{};
        Ipv4Header ip{};
        bytes data{};

        Ipv4Packet() = default;
        Ipv4Packet(const Ipv4Packet&) = default;

        Ipv4Packet(const bytes& pk) : Ipv4Packet(pk.data()) {}
        //     auto base = pk.begin();
        //     eth = EtherHeader(bytes(base, base += EtherHeader::size));
        //     ip = Ipv4Header(bytes(base, base + 12 + Ipv4Address::size + Ipv4Address::size));
        //     base += ip.header_size();
        //     data = bytes(base, pk.begin() + EtherHeader::size + ip.total_length);
        // }

        Ipv4Packet(const byte* pk) {
            auto base = pk;
            eth = EtherHeader(base);
            base += EtherHeader::size;
            ip = Ipv4Header(bytes(base, base + 12 + Ipv4Address::size + Ipv4Address::size));
            base += ip.header_size();
            data = bytes(base, pk + EtherHeader::size + ip.total_length);
        }
    };
}  // namespace network

#endif