#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include "headers/menu.hpp"
#include <stdio.h>
#include <vector>

void _examine_tcp_ports(_flags_info flags_info) noexcept {
    auto tcp_scanner = TCP_scanner(true);
    // if no modes specified, all modes for ports is the default
    if (flags_info.modes.size() == 0) {
        flags_info.modes.push_back(PortState::ALL);
    }

    for (const auto mode : flags_info.modes) {
        tcp_scanner.set_port_state(mode);
        if (flags_info.single_port != 0) {
            tcp_scanner.print_port_specified(flags_info.single_port);
        }
        if (flags_info.ranges.second != 0) {
            tcp_scanner.print_ports_ranged(flags_info.ranges.first, flags_info.ranges.second);
        }
    }
    std::cout << "------------------------------------------------------------\n";
}
void _examine_udp_ports(const _flags_info flags_info) noexcept {
    auto udp_scanner = UDP_scanner(true);
    if (flags_info.single_port != 0) {
        udp_scanner.print_port_specified(flags_info.single_port);
    }
    if (flags_info.ranges.second != 0) {
        udp_scanner.print_ports_ranged(flags_info.ranges.first, flags_info.ranges.second);
    }
    std::cout << "------------------------------------------------------------\n";
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

    // for each flag (tcp, udp, ipv4 address) - if set, examine it
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