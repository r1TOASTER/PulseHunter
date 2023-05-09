#pragma once
#include <winsock2.h>
#include <iphlpapi.h> 
#include <windows.h>
#include <memory>
#include "utils.hpp"

class TCP_scanner {
    public:
        [[nodiscard]] TCP_scanner(bool order) noexcept;
        void print_ports(PortState port_state) const noexcept;
        ~TCP_scanner() noexcept;
    private:
        std::unique_ptr<PMIB_TCPTABLE> _TcpTableHolder;
};