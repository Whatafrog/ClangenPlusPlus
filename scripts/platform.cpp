#include "platform.hpp"

int platform::getType() {
    #ifdef _WIN32
    return win32;
    #elif _WIN64
    return win64;
    #elif __APPLE__ || __MACH__
    return macOS;
    #elif __linux__
    return linux;
    #elif __unix || __unix__
    return unix;
    #else
    return NULL;
    #endif
} 

std::string platform::getName(const int type) {
    switch (type) {
        case win32:
            return "Windows 32-bit";
        case win64:
            return "Windows 64-bit";
        case macOS:
            return "macOS";
        case linux:
            return "Linux";
        case unix:
            return "Unix";
        default:
            return "Unsupported System";
    }
}