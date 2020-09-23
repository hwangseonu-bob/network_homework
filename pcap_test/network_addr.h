#pragma once

#include <string>
#include <ostream>
#include <cstdint>
#include <sstream>

struct HwAddr {
    uint8_t addr[6];

    std::string to_string() {
        std::stringstream strm;
        strm << this;
        return strm.str();
    }
};

std::ostream &operator<<(std::ostream &o, const HwAddr &a);

struct IpAddr {
    uint8_t addr[4];

    std::string to_string() {
        std::stringstream strm;
        strm << this;
        return strm.str();
    }
};

std::ostream &operator<<(std::ostream &o, const IpAddr &a);