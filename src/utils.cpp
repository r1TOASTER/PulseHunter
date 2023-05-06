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