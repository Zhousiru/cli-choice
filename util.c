#ifndef UTIL_C
#define UTIL_C

#include <stdio.h>

#define ENABLE_CLEAR 1

char getNumChar()
{
    printf("$ ");

    char ch;

    do
    {
        ch = getchar();
    } while (ch > '9' || ch < '0');

    return ch;
}

char clearConsole()
{
    if (ENABLE_CLEAR)
    {
        system("@cls||clear");
    }
    else
    {
        printf("\n----------------------------------------\n");
    }
}

#endif
