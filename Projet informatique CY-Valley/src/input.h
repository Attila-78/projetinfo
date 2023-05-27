#ifndef HEADER_INPUT
#define HEADER_INPUT 1
// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PLATFORM_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define PLATFORM_LINUX 1
#endif

#ifdef PLATFORM_WINDOWS
#include <conio.h>
#include <time.h>
#include <windows.h>

#endif

#ifdef PLATFORM_LINUX

#include <termios.h>
#include <unistd.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h> // nanosleep
#else
#include <unistd.h> // usleep
#endif
#endif

#define true 1
#define false 0

void platform_sleep(unsigned long long ms);
void platform_console_clear();
char quick_scanf();
void clean_input();
#endif