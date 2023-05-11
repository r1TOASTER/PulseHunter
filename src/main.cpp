#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include "headers/menu.hpp"
#include <stdio.h>
#include <vector>

void _examine_tcp_ports(const _flags_info flags_info) noexcept {

}
void _examine_udp_ports(const _flags_info flags_info) noexcept {
    
}
void _examine_ip_address(const _flags_info flags_info) noexcept {
    return;
}

int main(int argc, char* argv[]) {
    _flags_info flags_info = process_flags(argc, argv);

    // if didn't find flags, exit
    if (_flags_empty(flags_info)) {
        _fatal("Invalid flags provided");
    }

    // for each flag (tcp, udp, ipv4 address), examine it
    if (flags_info.tcp_enabled) {
        _examine_tcp_ports(flags_info);
    } 
    if (flags_info.udp_enabled) {
        _examine_udp_ports(flags_info);
    }
    if (flags_info.ip_address.size() > 0) {
        _examine_ip_address(flags_info);
    }

    return 0;
}