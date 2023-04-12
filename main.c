#include <time.h>
#include <windows.h>
#include "router.c"
#include "util.c"

int main()
{
    SetConsoleOutputCP(936);

    srand((unsigned int)time(NULL));

    int *router = (int *)malloc(sizeof(int));
    *router = VIEW_MAIN_MENU;
    for (;;)
    {
        clearConsole();

        routerRender(router);
    }
}
