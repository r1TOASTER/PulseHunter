#include "headers/TCPscanner.hpp"
#include <iostream>

PMIB_TCPTABLE TCP_scanner::Get_TCP_Table(bool order) {
    
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
    return return_table_as_raw;
}