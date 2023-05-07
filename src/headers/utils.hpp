#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <Windows.h>

enum class PortState {
    Closed = 1,
    Listen,
    SYN_sent,
    SYN_received,
    Established,
    FIN_wait1,
    FIN_wait2,
    Close_wait,
    Closing,
    Last_ACK,
    Time_wait,
    Delete_TCB,
    ALL,
};

extern void _fatal(const std::string msg);
extern void* _ulong_ec_malloc(ULONG size);
extern void* _dword_ec_malloc(DWORD size);
extern std::string _port_state_to_string(PortState port_state);

#endif