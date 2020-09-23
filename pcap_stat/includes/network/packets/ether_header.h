#ifndef __PCAP_STAT_ETHER_HEADER__
#define __PCAP_STAT_ETHER_HEADER__

#include <netinet/in.h>
#include <cstring>
#include "../address.h"
#include "../types.h"

namespace network {
    class EtherHeader {
       public:
        const static size_t size = 14;
        MacAddress dst{};
        MacAddress src{};
        uint16_t type{0x0800};

       public:
        EtherHeader() = default;
        EtherHeader(const EtherHeader &) = default;

        EtherHeader(const bytes &pk) : EtherHeader(pk.data()) {}

        EtherHeader(const byte *pk) {
            auto base = pk;
            dst = MacAddress(base);
            base += MacAddress::size;
            src = MacAddress(base);
            base += MacAddress::size;
            type = (base[0] << 8) + base[1];
        }

        operator bytes() {
            auto clone = EtherHeader(*this);
            clone.type = htons(clone.type);
            byte *ptr = reinterpret_cast<byte *>(&clone);
            return bytes(ptr, ptr + size);
        }
    };
}  // namespace network

#endif