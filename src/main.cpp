#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include <stdio.h>

int main() {
    auto ptr_tcp_table = TCP_scanner(true);
    auto ptr_udp_table = UDP_scanner(true);

    ptr_tcp_table.print_ports(PortState::ALL);
    ptr_udp_table.print_ports();

    return 0;
}