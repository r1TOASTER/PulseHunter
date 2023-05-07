#pragma once
#include <winsock2.h>
#include <iphlpapi.h> 
#include <windows.h>
#include <memory>
#include "utils.hpp"

class UDP_scanner {
    public:
        [[nodiscard]] UDP_scanner(bool order) noexcept;
        void print_ports() const noexcept;
    private:
        std::unique_ptr<MIB_UDPTABLE> _UdpTableHolder;
};