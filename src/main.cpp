#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include <stdio.h>

int main() {
    auto ptr_tcp_table = TCP_scanner::Get_TCP_Table(true);
    for (int i = 0; i < static_cast<int>(ptr_tcp_table->dwNumEntries); i++) {
        MIB_TCPROW* pTcpRow = &ptr_tcp_table->table[i];
        if (pTcpRow->dwState == MIB_TCP_STATE_LISTEN) {
            printf("(TCP) Port %u is open\n", ntohs(pTcpRow->dwLocalPort));
        }
    }
    auto ptr_udp_table = UDP_scanner::Get_UDP_Table(true);
    for (int i = 0; i < static_cast<int>(ptr_udp_table->dwNumEntries); i++) {
        MIB_UDPROW* pUdpRow = &ptr_udp_table->table[i];
        printf("(UDP) Port %u is open\n", ntohs(pUdpRow->dwLocalPort));
    }
    return 0;
}