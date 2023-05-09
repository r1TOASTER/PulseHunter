#include "headers/utils.hpp"

void _fatal(const std::string msg) {
    std::cerr << "(!) ERROR - " << msg << std::endl;
    exit(EXIT_FAILURE);
}

void* _ulong_ec_malloc(ULONG size) {
    auto ret = malloc(static_cast<std::size_t>(size));
    if (ret == nullptr) {
        _fatal("Failed to malloc memory for the size: " + size);
    }
    return ret;
}

void* _dword_ec_malloc(DWORD size) {
    auto ret = malloc(static_cast<std::size_t>(size));
    if (ret == nullptr) {
        _fatal("Failed to malloc memory for the size: " + size);
    }
    return ret;
}

std::string _port_state_to_string(PortState port_state) {
    switch (port_state) {
        case PortState::CLOSED:
            return "CLOSED";
            break;
        case PortState::LISTEN:
            return "LISTEN";
            break;
        case PortState::SYN_SENT:
            return "SYN_SENT";
            break;
        case PortState::SYN_RECEIVED:
            return "SYN_RECEIVED";
            break;
        case PortState::ESTABLISHED:
            return "ESTABLISHED";
            break;
        case PortState::FIN_WAIT1:
            return "FIN_WAIT1";
            break;
        case PortState::FIN_WAIT2:
            return "FIN_WAIT2";
            break;
        case PortState::CLOSE_WAIT:
            return "CLOSE_WAIT";
            break;
        case PortState::CLOSING:
            return "CLOSING";
            break;
        case PortState::LAST_ACK:
            return "LAST_ACK";
            break;
        case PortState::TIME_WAIT:
            return "TIME_WAIT";
            break;
        case PortState::DELETE_TCB:
            return "DELETE_TCB";
            break;
        case PortState::ALL:
            return "ALL";
            break;
    }
    return "Unknown";
}