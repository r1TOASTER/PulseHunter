#include "headers/TCPscanner.hpp"
#include "headers/UDPscanner.hpp"
#include "headers/menu.hpp"
#include <stdio.h>

void _examine_tcp_ports() noexcept {
    std::cout << "Enter 1 for examining a range of TCP ports, and 2 for a single port" << std::endl;
    int choice{};
    std::cin >> choice;
    switch (choice) {
        case 1:
        {
            std::cout << "Enter the range of the TCP ports to examine" << std::endl;

            int min_range{}, max_range{};
            std::cin >> min_range >> max_range;

            auto tcp_scanner = TCP_scanner(true);
            tcp_scanner.print_ports_ranged(min_range, max_range);
            break;
        }
        case 2:
        {
            std::cout << "Enter the TCP port's to examine" << std::endl;

            int udp_port{};
            std::cin >> udp_port;

            auto tcp_scanner = TCP_scanner(true);
            tcp_scanner.print_port_specified(udp_port);
            break;
        }
        default:
            std::cout << "Invalid choice. Returning to menu.\n" << std::endl;
            break;
    }
}

void _examine_udp_ports() noexcept {
    std::cout << "Enter 1 for examining a range of UDP ports, and 2 for a single port" << std::endl;
    int choice{};
    std::cin >> choice;
    switch (choice) {
        case 1:
        {
            std::cout << "Enter the range of the UDP ports to examine" << std::endl;

            int min_range{}, max_range{};
            std::cin >> min_range >> max_range;

            auto udp_scanner = UDP_scanner(true);
            udp_scanner.print_ports_ranged(min_range, max_range);
            break;
        }
        case 2:
        {
            std::cout << "Enter the UDP port's to examine" << std::endl;

            int udp_port{};
            std::cin >> udp_port;

            auto udp_scanner = UDP_scanner(true);
            udp_scanner.print_port_specified(udp_port);
            break;
        }
        default:
            std::cout << "Invalid choice. Returning to menu.\n" << std::endl;
            break;
    }
}
void _examine_ip_address() noexcept {
    return;
}

int main() {
    auto choice = 0;
    while (choice != 4) {
        choice = _main_menu_usage();
        switch (choice) {
        case 1:
            // Call a function to examine a specific TCP ports
            _examine_tcp_ports();
            break;
        case 2:
            // Call a function to examine a specific UDP ports
            _examine_udp_ports();
            break;
        case 3:
            // Call a function to examine a specific IP address 
            _examine_ip_address();
        case 4:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n" << std::endl;
            break;
        }
    }
    std::cout << "Exiting PulseHunter.\n" << std::endl;
    return 0;
}