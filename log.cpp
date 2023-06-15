#include "log.h"
#include <iostream>
#include <cstdarg>

void Log::error(const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    va_end(argptr);
    exit(1);
}

void Log::error(bool condition, const char* format, ...) {
    if (condition) {
        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);
        exit(1);
    }
}

void Log::write(const char* format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    va_end(argptr);
}