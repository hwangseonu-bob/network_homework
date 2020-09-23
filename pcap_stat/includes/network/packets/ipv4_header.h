#ifndef __PCAP_STAT_IPV4_HEADER__
#define __PCAP_STAT_IPV4_HEADER__

#include <netinet/in.h>
#include <cstring>
#include "../address.h"
#include "../types.h"

namespace network {
    class Ipv4Header {
       public:
        byte vihl{};
        byte tos{};
        uint16_t total_length{};
        uint16_t identification{};
        uint16_t flags{};
        byte ttl{};
        byte protocol{};
        uint16_t checksum{};
        Ipv4Address src;
        Ipv4Address dst;

       public:
        Ipv4Header() = default;
        Ipv4Header(const Ipv4Header &) = default;

        Ipv4Header(const bytes &pk) {
            std::memcpy(this, pk.data(), 12);
            total_length = ntohs(total_length);
            identification = ntohs(identification);
            flags = ntohs(flags);
            checksum = ntohs(checksum);
            auto base = pk.begin() + 12;
            src = Ipv4Address(bytes(base, base + Ipv4Address::size));
            base += Ipv4Address::size;
            dst = Ipv4Address(bytes(base, base + Ipv4Address::size));
        }

        Ipv4Header(const byte *pk) : Ipv4Header(bytes(pk, pk + 12 + Ipv4Address::size + Ipv4Address::size)) {}

        size_t header_size() const { return (vihl & 0xF) << 2; }

        operator bytes() {
            auto clone = Ipv4Header(*this);
            clone.total_length = htons(total_length);
            clone.identification = htons(identification);
            clone.flags = htons(flags);
            clone.checksum = htons(checksum);
            byte *ptr = reinterpret_cast<byte *>(&clone);
            return bytes(ptr, ptr + header_size());
        }
    };
}  // namespace network

#endif