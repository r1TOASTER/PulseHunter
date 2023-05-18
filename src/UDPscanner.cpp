#include "headers/UDPscanner.hpp"

UDP_scanner::~UDP_scanner() noexcept {
    free(_UdpTableHolder.release());
}

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
        auto current_port = ntohs(pUdpRow->dwLocalPort);
        printf("(UDP) Port %u is open\n", current_port);
    }
}

void UDP_scanner::print_ports_ranged(const int low_range, const int high_range) const noexcept {
    auto raw = *(_UdpTableHolder);
    int count = 0;
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); i++) {
        MIB_UDPROW* pUdpRow = &(raw->table[i]);
        auto current_port = ntohs(pUdpRow->dwLocalPort);
        if ((current_port >= low_range) && (current_port <= high_range)) {
            count++;
            printf("(UDP) Port %u is open\n", current_port);
        }
    }
    if (count == 0) {
        printf("There are no UDP ports in the range [ %d - %d ] to examine\n", low_range, high_range);
    }
}

void UDP_scanner::print_port_specified(const int port) const noexcept {
    auto raw = *(_UdpTableHolder);
    int count = 0;
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); i++) {
        MIB_UDPROW* pUdpRow = &(raw->table[i]);
        auto current_port = ntohs(pUdpRow->dwLocalPort);
        if (current_port == port) {
            count++;
            printf("(UDP) Port %u is open\n", current_port);
        }
    }
    if (count == 0) {
        printf("There is no such UDP port [ %u ] to examine\n", port);
    }
}

void UDP_scanner::scan_ip_address(const DWORD ip_address) const noexcept {
    auto raw = *(_UdpTableHolder);
    int count = 0;
    for (int i = 0; i < static_cast<int>(raw->dwNumEntries); ++i) {
        MIB_UDPROW* pUdpRow = &(raw->table[i]);
        auto dwLocalAddr = pUdpRow->dwLocalAddr;
        if (dwLocalAddr == ip_address) { // the specified ip is found as a local addr
            count++;
            std::cout << "Local address found in UDP connection. "
                      << "Using port: " << ntohs(pUdpRow->dwLocalPort) << '\n'; 
        }
    }
    if (count == 0) {
        printf("The IP address specified isn't a local / remote address currently active in any TCP connection.");
    }
}

UDP_scanner::UDP_scanner(const UDP_scanner& rhs) noexcept : _UdpTableHolder(nullptr) {
    if (rhs._UdpTableHolder != nullptr) {
        _UdpTableHolder = std::make_unique<PMIB_UDPTABLE>(*rhs._UdpTableHolder);
    }
}

UDP_scanner& UDP_scanner::operator=(const UDP_scanner& rhs) noexcept {
    if (!rhs._UdpTableHolder) {
        _UdpTableHolder.reset();
    }
    else if (!_UdpTableHolder) {
        _UdpTableHolder = std::make_unique<PMIB_UDPTABLE>(*rhs._UdpTableHolder);
    }
    else {
        *_UdpTableHolder = *rhs._UdpTableHolder;
    }
    return *this;
}