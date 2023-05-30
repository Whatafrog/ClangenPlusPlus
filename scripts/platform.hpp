#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>

enum platform_type { win32, win64, macOS, linux, unix };

namespace platform {
    int getType();
    std::string getName(const int type);
}

#endif