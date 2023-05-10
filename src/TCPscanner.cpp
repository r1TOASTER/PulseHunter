#include "headers/TCPscanner.hpp"
#include <iostream>

TCP_scanner::~TCP_scanner() noexcept {
    free(_TcpTableHolder.release());
}

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
    _TcpTableHolder = std::make_unique<PMIB_TCPTABLE>(return_table_as_raw);
}

void TCP_scanner::print_ports(PortState port_state) const noexcept {
    auto raw = *(_TcpTableHolder);
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); ++i) {
        MIB_TCPROW* pTcpRow = &(raw->table[i]);
        if (port_state == PortState::ALL) {
            printf("(TCP) Port %u is in the state: %s\n", ntohs(pTcpRow->dwLocalPort), _port_state_to_string(static_cast<PortState>(pTcpRow->dwState)).c_str());
        }
        else if (pTcpRow->dwState == static_cast<DWORD>(port_state)) {
            printf("(TCP) Port %u is in the state: %s\n", ntohs(pTcpRow->dwLocalPort), _port_state_to_string(port_state).c_str());
        }
    }
}

void TCP_scanner::print_ports_ranged(int low_range, int high_range) const noexcept {
    auto raw = *(_TcpTableHolder);
    int count = 0;
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); ++i) {
        MIB_TCPROW* pTcpRow = &(raw->table[i]);
        auto current_port = ntohs(pTcpRow->dwLocalPort);
        if ((current_port >= low_range) && (current_port <= high_range)) {
            count++;
            printf("(TCP) Port %u is in the state: %s\n", current_port, _port_state_to_string(static_cast<PortState>(pTcpRow->dwState)).c_str());
        }
    }
    if (count == 0) {
        printf("There are no TCP ports in the range [ %d - %d ] to examine\n", low_range, high_range);
    }
}

void TCP_scanner::print_port_specified(int port) const noexcept {
    auto raw = *(_TcpTableHolder);
    int count = 0;
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); ++i) {
        MIB_TCPROW* pTcpRow = &(raw->table[i]);
        auto current_port = ntohs(pTcpRow->dwLocalPort);
        if (port == current_port) {
            count++;
            printf("(TCP) Port %u is in the state: %s\n", current_port, _port_state_to_string(static_cast<PortState>(pTcpRow->dwState)).c_str());
        }
    }
    if (count == 0) {
        printf("There is no such TCP port [ %u ] to examine\n", port);
    }
}