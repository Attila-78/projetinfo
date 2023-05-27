#include "input.h"
#include <stdio.h>
#include <stdlib.h>

// choisis la bonne fonction en fonction de l'OS
#ifdef PLATFORM_WINDOWS

void platform_sleep(unsigned long long ms)
{
    Sleep(ms);
}
void platform_console_clear()
{
    system("cls");
}

#elif defined(PLATFORM_LINUX)

void platform_sleep(unsigned long long ms)
{
#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;
    nanosleep(&ts, 0);
#else
    if (ms >= 1000)
    {
        sleep(ms / 1000);
    }
    usleep((ms % 1000) * 1000);
#endif
}

void platform_console_clear()
{
    printf("\033[H\033[J");
}
#endif

// fait un scanf, mais n'attend pas l'utilisateur pour appuyer entrée
char quick_scanf()
{
#ifdef PLATFORM_WINDOWS
    if (_kbhit())
    {
        return _getch();
    }
#elif defined(PLATFORM_LINUX)
    return getchar();
#endif
}

// enleve la file d'attente des entrées
void clean_input()
{
    while (getchar() != '\n')
    {
        // boucle
    }
}