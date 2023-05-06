#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <Windows.h>

extern void _fatal(const std::string msg);
extern void* _ulong_ec_malloc(ULONG size);
extern void* _dword_ec_malloc(DWORD size);

#endif