#include "network_addr.h"

std::ostream &operator<<(std::ostream &o, const HwAddr &a) {
    char buff[20];
    sprintf(buff, "%02X:%02X:%02X:%02X:%02X:%02X", a.addr[0], a.addr[1], a.addr[2], a.addr[3], a.addr[4], a.addr[5]);
    return o << std::string(buff);
}

std::ostream &operator<<(std::ostream &o, const IpAddr &a) {
    char buff[20];
    sprintf(buff, "%d.%d.%d.%d", a.addr[0], a.addr[1], a.addr[2], a.addr[3]);
    return o << std::string(buff);
}