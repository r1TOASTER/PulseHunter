#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include "headers/menu.hpp"
#include <stdio.h>
#include <sstream>
#include <optional>
#include <vector>

void _examine_tcp_ports(_flags_info flags_info, TCP_scanner tcp_scanner) noexcept {
    std::cout << "\nTCP SECTION: \n";
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
        else if (flags_info.ranges.second == 0 && flags_info.single_port == 0) {
            tcp_scanner.print_ports();
        }
    }
    std::cout << "\n";
}

void _examine_udp_ports(const _flags_info flags_info, const UDP_scanner udp_scanner) noexcept {
    std::cout << "\nUDP SECTION: \n";
    if (flags_info.single_port != 0) {
        udp_scanner.print_port_specified(flags_info.single_port);
    }
    if (flags_info.ranges.second != 0) {
        udp_scanner.print_ports_ranged(flags_info.ranges.first, flags_info.ranges.second);
    }
    else if (flags_info.ranges.second == 0 && flags_info.single_port == 0) {
        udp_scanner.print_ports();
    }
    std::cout << "\n";
}

void _examine_ip_address(const _flags_info flags_info, const UDP_scanner udp_scanner,
                         const TCP_scanner tcp_scanner) noexcept {
    DWORD dword_ip_address = inet_addr(flags_info.ip_address.c_str());
    if (dword_ip_address == INADDR_NONE) {
        _fatal("Invalid IP address provided");
    }

    std::cout << "\nIP ADDRESS SECTION: \n";
    tcp_scanner.scan_ip_address(dword_ip_address);
    std::cout << '\n';
    udp_scanner.scan_ip_address(dword_ip_address);

    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    _flags_info flags_info = process_flags(argc, argv);

    // if didn't find flags, exit
    if (_flags_empty(flags_info)) {
        _fatal("Invalid flags provided");
    }

    UDP_scanner udp_scanner(true);
    TCP_scanner tcp_scanner(true);

    // for each flag (tcp, udp, ipv4 address) - if set, examine it
    if (flags_info.tcp_enabled) {
        _examine_tcp_ports(flags_info, tcp_scanner);
    } 
    if (flags_info.udp_enabled) {
        _examine_udp_ports(flags_info, udp_scanner);
    }
    if (flags_info.ip_address.size() > 0) {
        _examine_ip_address(flags_info, udp_scanner, tcp_scanner);
    }

    return 0;
}