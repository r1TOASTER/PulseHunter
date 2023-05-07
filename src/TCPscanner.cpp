#include "headers/TCPscanner.hpp"
#include <iostream>

[[nodiscard]] TCP_scanner::TCP_scanner(bool order) noexcept {
    
    PMIB_TCPTABLE return_table_as_raw;
    DWORD dwSize = 0;

    // getting the table's size
    auto ResultForSizeOfPointer = GetTcpTable(nullptr, &dwSize, order);
    if (ResultForSizeOfPointer != ERROR_INSUFFICIENT_BUFFER) {
        _fatal("Failed to get TCP table for it's size");
    }

    // mallocing the size, and getting the table
    return_table_as_raw = (PMIB_TCPTABLE) _dword_ec_malloc(dwSize); 
    auto ResultTcpTable = GetTcpTable(return_table_as_raw, &dwSize, order);
    if (ResultTcpTable != NO_ERROR) {
        _fatal("Failed to get TCP table after successfully retrieving it's size");
    }

    // returning the table
    _TcpTableHolder = std::make_unique<MIB_TCPTABLE>(*return_table_as_raw);
}

void TCP_scanner::print_ports(PortState port_state) const noexcept {
    for (int i = 0; i < static_cast<int>(_TcpTableHolder->dwNumEntries); i++) {
        MIB_TCPROW* pTcpRow = &_TcpTableHolder->table[i];
        if (port_state == PortState::ALL) {
            printf("(TCP) Port %u is in the state: %s\n", ntohs(pTcpRow->dwLocalPort), _port_state_to_string((PortState) pTcpRow->dwState).c_str());
        }
        else if (pTcpRow->dwState == (DWORD) port_state) {
            printf("(TCP) Port %u is in the state: %s\n", ntohs(pTcpRow->dwLocalPort), _port_state_to_string(port_state).c_str());
        }
    }
}