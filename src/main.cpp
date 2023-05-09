#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include <stdio.h>

int main() {
    auto tcp_table = TCP_scanner(true);
    auto udp_table = UDP_scanner(true);

    tcp_table.print_ports(PortState::ALL);
    udp_table.print_ports();

    return 0;
}