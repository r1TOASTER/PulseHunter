#include "headers/menu.hpp"
#include <iostream>

int _main_menu_usage() noexcept {
    std::cout << "PulseHunter" << std::endl;
    std::cout << "To use PulseHunter, please enter one of the following options:" << std::endl;
    std::cout << "1. Examine a specific TCP ports (single or more)" << std::endl;
    std::cout << "2. Examine a specific UDP ports (single or more)" << std::endl;
    std::cout << "3. Examine a specific IP address" << std::endl;
    std::cout << "4. Quit PulseHunter" << std::endl;
    
    int choice{};
    std::cout << "Please enter your choice: ";
    std::cin >> choice;
    
    return choice;
}