#pragma once
#include <winsock2.h>
#include <iphlpapi.h> 
#include <windows.h>
#include <memory>
#include "utils.hpp"

class UDP_scanner {
    public:
        [[nodiscard]] UDP_scanner(bool order) noexcept;
        ~UDP_scanner() noexcept;
        
        void print_ports() const noexcept;
        void print_ports_ranged(int low_range, int high_range) const noexcept;
        void print_port_specified(int port) const noexcept;

        UDP_scanner(const UDP_scanner& rhs) noexcept;
        UDP_scanner& operator=(const UDP_scanner& rhs) noexcept;
    private:
        std::unique_ptr<PMIB_UDPTABLE> _UdpTableHolder;
};
