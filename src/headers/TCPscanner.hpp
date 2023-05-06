#pragma once
#include <winsock2.h>
#include <iphlpapi.h> 
#include <windows.h>
#include "utils.hpp"

namespace TCP_scanner{
    PMIB_TCPTABLE Get_TCP_Table(bool order);
};