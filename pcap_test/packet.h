#pragma once

#include <iostream>
#include <cstdint>
#include <netinet/in.h>
#include "network_addr.h"

struct EtherHeader {
    HwAddr dst;
    HwAddr src;
    uint16_t ether_type;

    int type() const;
};

std::ostream &operator<<(std::ostream &o, const EtherHeader& eth);

struct IpHeader {
    uint8_t version_ihl;
    uint8_t type_of_service;
    uint16_t packet_length;
    uint16_t identifier;
    uint16_t flags_fragment_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    IpAddr sip;
    IpAddr dip;

    int length() const;

    int total_length() const;
};

std::ostream &operator<<(std::ostream& o, const IpHeader& ip);

struct TcpHeader {
    uint16_t src;
    uint16_t dst;
    uint32_t seq;
    uint32_t ack;
    uint16_t hl_rb_flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_ptr;

    int length() const;
    int sport() const;
    int dport() const;
};

void print_tcp_data(int packet_length, int tcp_index, const uint8_t *packet);

std::ostream &operator<<(std::ostream &o, const TcpHeader& tcp);