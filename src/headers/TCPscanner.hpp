#pragma once
#include <winsock2.h>
#include <iphlpapi.h> 
#include <windows.h>
#include <memory>
#include "utils.hpp"

class TCP_scanner {
    public:
        [[nodiscard]] TCP_scanner(bool order) noexcept;
        ~TCP_scanner() noexcept;
        
        void print_ports(PortState port_state) const noexcept;
        void print_ports_ranged(int low_range, int high_range) const noexcept;
        void print_port_specified(int port) const noexcept;
    private:
        std::unique_ptr<PMIB_TCPTABLE> _TcpTableHolder;
};