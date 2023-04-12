#ifndef ROUTER_C
#define ROUTER_C

#include <stdio.h>
#include "view.c"
#include "util.c"

void routerRender(int *router)
{
    switch (*router)
    {
    case VIEW_MAIN_MENU:
        viewMainMenu(router);
        break;

    case VIEW_QUESTION_EXPLORER:
        viewQuestionExplorer(router, 0);
        break;

    case VIEW_QUESTION_EDITOR:
        viewQuestionExplorer(router, 1);
        break;

    case VIEW_RANDOM_TEST:
        viewRandomTest(router);
        break;

    default:
        printf("Error: 无效路由\n [0] 返回主菜单\n");
        *router = getNumChar() - '0';
        break;
    }
}

#endif
