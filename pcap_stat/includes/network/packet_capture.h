#ifndef __PCAP_STAT_PACKET_CAPTURE__
#define __PCAP_STAT_PACKET_CAPTURE__

#include <pcap.h>
#include <stdexcept>
#include <string>
#include "types.h"

namespace network {
    class PacketCapture {
       private:
        pcap_t *handle;

       public:
        PacketCapture(const std::string &filename) {
            char errbuf[PCAP_ERRBUF_SIZE] = {0};
            handle = pcap_open_offline(filename.c_str(), errbuf);
            if (handle == nullptr) throw std::runtime_error(errbuf);
        }

        ~PacketCapture() {
            pcap_close(handle);
        }

        bytes next() const {
            pcap_pkthdr *header;
            const byte *packet = new byte[2048];

            int res = pcap_next_ex(handle, &header, &packet);

            if (res <= 0) {
                delete packet;
                return bytes();
            }
            bytes pk(packet, packet + header->caplen);
            return pk;
        }
    };
}  // namespace network

#endif