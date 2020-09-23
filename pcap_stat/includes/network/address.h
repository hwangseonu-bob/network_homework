#ifndef __PCAP_STAT_NETWORK_ADDRESS__
#define __PCAP_STAT_NETWORK_ADDRESS__

#include <ostream>
#include <string>
#include "types.h"

namespace network {
    class MacAddress {
       private:
        bytes addr{size};

       public:
        static const size_t size = 6;

        MacAddress() = default;
        MacAddress(const MacAddress&) = default;

        MacAddress(const bytes& mac) : addr(mac) {}
        MacAddress(const byte* mac) : addr(bytes(mac, mac + size)) {}

        operator bytes() const { return addr; }
        operator std::string() const {
            char str[18];
            sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
            return std::string(str);
        }

        bool operator==(const MacAddress& other) const { return addr == other.addr; }
        bool operator!=(const MacAddress& other) const { return addr != other.addr; }
        bool operator<(const MacAddress& other) const { return addr < other.addr; }
        bool operator>(const MacAddress& other) const { return addr > other.addr; }
        bool operator<=(const MacAddress& other) const { return addr <= other.addr; }
        bool operator>=(const MacAddress& other) const { return addr >= other.addr; }
    };

    std::ostream& operator<<(std::ostream& o, const MacAddress& mac) { return o << std::string(mac); }

    class Ipv4Address {
       private:
        bytes addr{size};

       public:
        static const size_t size = 4;

        Ipv4Address() = default;
        Ipv4Address(const Ipv4Address&) = default;

        Ipv4Address(const bytes& ip) : addr(ip) {}
        Ipv4Address(const byte* ip) : addr(bytes(ip, ip + size)) {}

        operator bytes() const { return addr; }
        operator std::string() const {
            char str[16];
            sprintf(str, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
            return std::string(str);
        }

        bool operator==(const Ipv4Address& other) const { return addr == other.addr; }
        bool operator!=(const Ipv4Address& other) const { return addr != other.addr; }
        bool operator<(const Ipv4Address& other) const { return addr < other.addr; }
        bool operator>(const Ipv4Address& other) const { return addr > other.addr; }
        bool operator<=(const Ipv4Address& other) const { return addr <= other.addr; }
        bool operator>=(const Ipv4Address& other) const { return addr >= other.addr; }
    };

    std::ostream& operator<<(std::ostream& o, const Ipv4Address& ip) { return o << std::string(ip); }
}  // namespace network

#endif