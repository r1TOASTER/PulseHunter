#include "headers/UDPscanner.hpp"

[[nodiscard]] UDP_scanner::UDP_scanner(bool order) noexcept {
    
    PMIB_UDPTABLE return_table_as_raw;
    DWORD dwSize = 0;

    // getting the table's size
    auto ResultForSizeOfPointer = GetUdpTable(nullptr, &dwSize, order);
    if (ResultForSizeOfPointer != ERROR_INSUFFICIENT_BUFFER) {
        _fatal("Failed to get TCP table for it's size");
    }

    // mallocing the size, and getting the table
    return_table_as_raw = (PMIB_UDPTABLE) _dword_ec_malloc(dwSize); 
    auto ResultTcpTable = GetUdpTable(return_table_as_raw, &dwSize, order);
    if (ResultTcpTable != NO_ERROR) {
        _fatal("Failed to get TCP table after successfully retrieving it's size");
    }

    // returning the table
    _UdpTableHolder = std::make_unique<PMIB_UDPTABLE>(return_table_as_raw);
}

void UDP_scanner::print_ports() const noexcept {
    auto raw = *(_UdpTableHolder);
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); i++) {
        MIB_UDPROW* pUdpRow = &(raw->table[i]);
        printf("(UDP) Port %u is open\n", ntohs(pUdpRow->dwLocalPort));
    }
}