#ifndef __PCAP_STAT_STATISTICS__
#define __PCAP_STAT_STATISTICS__

#include <map>
#include <ostream>
#include <string>
#include "./packets/ipv4.h"
#include "packet_capture.h"
#include "types.h"

namespace network {
    struct Statistic {
        struct PacketAmount {
            int packets{0};
            int bytes{0};

            PacketAmount& operator+=(int bytes) {
                this->packets++;
                this->bytes += bytes;
                return *this;
            }
        };

        PacketAmount tx;
        PacketAmount rx;
    };

    template <class T>
    class EnpointsStatistic {
       private:
        std::map<T, Statistic> stat_map;

       public:
        EnpointsStatistic() = default;

        void add(const T& key, const bytes& pk, bool is_tx) {
            auto it = stat_map.find(key);

            if (it == stat_map.end()) {
                Statistic stat;
                if (is_tx)
                    stat.tx += pk.size();
                else
                    stat.rx += pk.size();
                stat_map.insert(std::make_pair(key, stat));
            } else {
                if (is_tx)
                    it->second.tx += pk.size();
                else
                    it->second.rx += pk.size();
            }
        }

        friend std::ostream& operator<<(std::ostream& o, const EnpointsStatistic<T>& stat) {
            o << "=== Endpoints ===" << std::endl;
            o << "Address"
              << "\t\t\t"
              << "Packets"
              << "\t\t"
              << "Bytes"
              << "\t\t"
              << "Tx Packets"
              << "\t"
              << "Tx Bytes"
              << "\t"
              << "Rx Packets"
              << "\t"
              << "Rx Bytes"
              << std::endl;

            for (auto& i : stat.stat_map) {
                auto s = i.second;

                o << i.first;
                o << "\t" << s.tx.packets + s.rx.packets << "\t\t" << s.tx.bytes + s.rx.bytes;
                o << "\t\t" << s.tx.packets << "\t\t" << s.tx.bytes;
                o << "\t\t" << s.rx.packets << "\t\t" << s.rx.bytes;
                o << std::endl;
            }
            return o;
        }
    };

    template <class T>
    class ConversationsStatistic {
       private:
        std::map<std::pair<T, T>, Statistic> stat_map;

       public:
        ConversationsStatistic() = default;

        void add(const T& src, const T& dst, const bytes& pk) {
            auto key = src <= dst ? std::make_pair(src, dst) : std::make_pair(dst, src);
            auto it = stat_map.find(key);

            if (it == stat_map.end()) {
                Statistic stat;
                if (src <= dst)
                    stat.tx += pk.size();
                else
                    stat.rx += pk.size();
                stat_map.insert(std::make_pair(key, stat));
            } else {
                if (src <= dst)
                    it->second.tx += pk.size();
                else
                    it->second.rx += pk.size();
            }
        }

        friend std::ostream& operator<<(std::ostream& o, const ConversationsStatistic<T>& stat) {
            o << "=== Conversations ===" << std::endl;
            o << "Address(A)"
              << "\t\t"
              << "Address(B)"
              << "\t\t"
              << "Packets"
              << "\t\t"
              << "Bytes"
              << "\t\t"
              << "Packets A -> B"
              << "\t"
              << "Bytes A -> B"
              << "\t"
              << "Packets B -> A"
              << "\t"
              << "Bytes B -> A"
              << std::endl;

            for (auto& i : stat.stat_map) {
                auto s = i.second;

                o << i.first.first << "\t" << i.first.second;
                o << "\t" << s.tx.packets + s.rx.packets << "\t\t" << s.tx.bytes + s.rx.bytes;
                o << "\t\t" << s.tx.packets << "\t\t" << s.tx.bytes;
                o << "\t\t" << s.rx.packets << "\t\t" << s.rx.bytes;
                o << std::endl;
            }
            return o;
        }
    };

}  // namespace network

#endif