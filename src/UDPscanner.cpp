#include "headers/UDPscanner.hpp"

PMIB_UDPTABLE UDP_scanner::Get_UDP_Table(bool order) {
    
    PMIB_UDPTABLE return_table_as_raw;
    ULONG ulSize = 0;

    // getting the table's size
    auto ResultForSizeOfPointer = GetUdpTable(nullptr, &ulSize, order);
    if (ResultForSizeOfPointer != ERROR_INSUFFICIENT_BUFFER) {
        _fatal("Failed to get UDP table for it's size");
    }

    // mallocing the size, and getting the table
    return_table_as_raw = (PMIB_UDPTABLE) _ulong_ec_malloc(ulSize); 
    auto ResultUdpTable = GetUdpTable(return_table_as_raw, &ulSize, order);
    if (ResultUdpTable != NO_ERROR) {
        _fatal("Failed to get UDP table after successfully retrieving it's size");
    }

    // returning the table
    return return_table_as_raw;
}