#include "headers/menu.hpp"
#include <iostream>

void _usage() noexcept {
    std::cout << "Usage: PulseHunter [-h] [-t] [-u] [-m MODES] [-r RANGE_START RANGE_END] [-s SINGLE_PORT] [-i IP_ADDRESS]" << std::endl;
    std::cout << "Flags:" << std::endl;
    std::cout << "  -h\t\tDisplay this help message" << std::endl;
    std::cout << "  -t\t\tSpecify TCP ports to scan" << std::endl;
    std::cout << "  -u\t\tSpecify UDP ports to scan" << std::endl;
    std::cout << "  -m MODES\tSpecify modes to display (c, l, t, d, e, f, k, w, b, a)" << std::endl;
    std::cout << "\t\tc: Display information about all connections that are in the CLOSED, CLOSE_WAIT, or CLOSING states." << std::endl;
    std::cout << "\t\tl: Display information about all connections that are in the LISTEN state." << std::endl;
    std::cout << "\t\tt: Display information about all connections that are in the SYN_SENT state." << std::endl;
    std::cout << "\t\td: Display information about all connections that are in the SYN_RECEIVED state." << std::endl;
    std::cout << "\t\te: Display information about all connections that are in the ESTABLISHED state." << std::endl;
    std::cout << "\t\tf: Display information about all connections that are in the FIN_WAIT1 or FIN_WAIT2 states." << std::endl;
    std::cout << "\t\tk: Display information about all connections that are in the LAST_ACK state." << std::endl;
    std::cout << "\t\tw: Display information about all connections that are in the TIME_WAIT state." << std::endl;
    std::cout << "\t\tb: Delete the TCB (Transmission Control Block) for a connection." << std::endl;
    std::cout << "\t\ta: Display information about all connection modes." << std::endl;
    std::cout << "  -r RANGE_START RANGE_END\tSpecify a range of ports to scan (e.g. 10 200)" << std::endl;
    std::cout << "  -s SINGLE_PORT\tSpecify a single port to scan" << std::endl;
    std::cout << "  -i IP_ADDRESS\tSpecify an IPv4 address to examine" << std::endl;
}

_flags_info process_flags(const int argc, char* argv[]) noexcept {
    std::vector<PortState> modes{};
    bool tcp = false, udp = false;
    int range_start = 0;
    int range_end = 0;
    int single_port = 0;
    std::string ip_address{};

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            _usage();
            exit(EXIT_SUCCESS);
        } else if (arg == "-t") {
            tcp = true;
        } else if (arg == "-u") {
            udp = true;
        }
        else if (arg == "-m") {
            if (i < argc - 1) {
                std::string modes_str = argv[++i];
                for (char c : modes_str) {
                    switch (c) {
                        case 'c':
                            modes.push_back(PortState::CLOSED);
                            modes.push_back(PortState::CLOSE_WAIT);
                            modes.push_back(PortState::CLOSING);
                            break;
                        case 'l':
                            modes.push_back(PortState::LISTEN);
                            break;
                        case 't':
                            modes.push_back(PortState::SYN_SENT);
                            break;
                        case 'd':
                            modes.push_back(PortState::SYN_RECEIVED);
                            break;
                        case 'e':
                            modes.push_back(PortState::ESTABLISHED);
                            break;
                        case 'f':
                            modes.push_back(PortState::FIN_WAIT1);
                            modes.push_back(PortState::FIN_WAIT2);
                            break;
                        case 'k':
                            modes.push_back(PortState::LAST_ACK);
                            break;
                        case 'w':
                            modes.push_back(PortState::TIME_WAIT);
                            break;
                        case 'b':
                            modes.push_back(PortState::DELETE_TCB);
                            break;
                        case 'a':
                            modes.push_back(PortState::ALL);
                            break;
                        default:
                            std::cerr << "Unknown mode: " << c << std::endl;
                            break;
                        }
                  }
            } 
            else {
                std::cerr << "Missing argument for -m flag" << std::endl;
            }   
        }
        else if (arg == "-r") {
            if (i < argc - 2) {
                try {
                    range_start = std::stoi(argv[++i]);
                    range_end = std::stoi(argv[++i]);
                    if (range_start > range_end) {
                        // reversing the ports numbers (200 10 -> 10 200)
                        auto reverse = range_start;
                        range_start = range_end;
                        range_end = reverse;
                    }
                } catch (const std::invalid_argument& e) {
                    _fatal("Invalid argument provided for -r flag");
                }
            } else {
                std::cerr << "Invalid number of arguments for -r flag" << std::endl;
            }
        } else if (arg == "-s") {
            if (i < argc - 1) {
                try {
                    single_port = std::stoi(argv[++i]);
                } catch (const std::invalid_argument& e) {
                    _fatal("Invalid argument provided for -s flag");
                }
            } else {
                std::cerr << "Invalid number of arguments for -s flag" << std::endl;
            }
        } else if (arg == "-i") {
            if (i < argc - 1) {
                ip_address = argv[++i];
            } else {
                std::cerr << "Invalid number of arguments for -i flag" << std::endl;
            }
        }
    }

    return {
        tcp,
        udp,
        modes,
        std::make_pair(range_start, range_end),
        single_port,
        ip_address,
    };
}

bool _flags_empty(const _flags_info flags) noexcept {
    return (flags.tcp_enabled == false && flags.udp_enabled == false 
            && flags.single_port == 0 && flags.ranges.first == 0
            && flags.ranges.second == 0 && flags.modes.size() == 0
            && flags.ip_address == "");
}