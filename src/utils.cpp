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
<<<<<<< HEAD

std::string _port_state_to_string(PortState port_state) {
    switch (port_state) {
        case PortState::Closed:
            return "Closed";
            break;
        case PortState::Listen:
            return "Listening";
            break;
        case PortState::SYN_sent:
            return "SYN_sent";
            break;
        case PortState::SYN_received:
            return "SYN_received";
            break;
        case PortState::Established:
            return "Established";
            break;
        case PortState::FIN_wait1:
            return "FIN_wait1";
            break;
        case PortState::FIN_wait2:
            return "FIN_wait2";
            break;
        case PortState::Close_wait:
            return "Close_wait";
            break;
        case PortState::Closing:
            return "Closing";
            break;
        case PortState::Last_ACK:
            return "Last_ACK";
            break;
        case PortState::Time_wait:
            return "Time_wait";
            break;
        case PortState::Delete_TCB:
            return "Delete_TCB";
            break;
        case PortState::ALL:
            return "ALL";
            break;
    }
    return "Unknown";
}
=======
>>>>>>> f06900ac53c2e6f5146a5baffd0be8e564384165
