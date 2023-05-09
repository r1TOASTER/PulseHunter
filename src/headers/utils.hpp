#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <Windows.h>

enum class PortState : DWORD {
    CLOSED     =  0x00000001,
    LISTEN     =  0x00000002,
    SYN_SENT   =  0x00000003,
    SYN_RECEIVED =  0x00000004,
    ESTABLISHED =  0x00000005,
    FIN_WAIT1  =  0x00000006,
    FIN_WAIT2  =  0x00000007,
    CLOSE_WAIT =  0x00000008,
    CLOSING    =  0x00000009,
    LAST_ACK   = 0x0000000A,
    TIME_WAIT  = 0x0000000B,
    DELETE_TCB = 0x0000000C,
    ALL = 0x0000000D,
};

extern void _fatal(const std::string msg);
extern void* _ulong_ec_malloc(ULONG size);
extern void* _dword_ec_malloc(DWORD size);
extern std::string _port_state_to_string(PortState port_state);

#endif