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
        
        void print_ports() const noexcept;
        void print_ports_ranged(const int low_range,const int high_range) const noexcept;
        void print_port_specified(const int port) const noexcept;
        void set_port_state(const PortState& port_state) noexcept;

        [[nodiscard]] TCP_scanner(const TCP_scanner& rhs) noexcept;
        [[nodiscard]] TCP_scanner& operator=(const TCP_scanner& rhs) noexcept;
    private:
        std::unique_ptr<PMIB_TCPTABLE> _TcpTableHolder;
        PortState _portState = PortState::ALL;
};
