#pragma once
#include <vector>
#include <string>
#include <utility>
#include "utils.hpp"
#include <stdexcept>

typedef struct _flags_info {
    bool tcp_enabled;
    bool udp_enabled;
    std::vector<PortState> modes;
    std::pair<int, int> ranges;
    int single_port;
    std::string ip_address;
} _flags_info;

extern void _usage() noexcept;
extern _flags_info process_flags(const int argc, char* argv[]) noexcept;
extern bool _flags_empty(const _flags_info flags) noexcept;