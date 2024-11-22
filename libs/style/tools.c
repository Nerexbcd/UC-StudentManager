#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

void clearConsole()
{
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}