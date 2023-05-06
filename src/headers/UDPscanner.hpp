#pragma once
#include <winsock2.h>
#include <iphlpapi.h> 
#include <windows.h>
#include "utils.hpp"

namespace UDP_scanner {
    PMIB_UDPTABLE Get_UDP_Table(bool order);
};