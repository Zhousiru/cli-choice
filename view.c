#ifndef VIEW_C
#define VIEW_C

#include <stdio.h>
#include <stdlib.h>
#include "router.c"
#include "util.c"
#include "question.c"
#include "linkedlist.c"

#define VIEW_MAIN_MENU 0
#define VIEW_QUESTION_EXPLORER 1
#define VIEW_QUESTION_EDITOR 2
#define VIEW_RANDOM_TEST 3

void viewMainMenu(int *router)
{
    printf("╭────────────────────────────────────────────╮\n");
    printf("│          单项选择题标准化考试系统          │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╭────────────────────────────────────────────╮\n");
    printf("│                   主菜单                   │\n");
    printf("├────────────────────────────────────────────┤\n");
    printf("│                                            │\n");
    printf("│                [1] 浏览题目                │\n");
    printf("│                [2] 题目编辑                │\n");
    printf("│                [3] 抽题作答                │\n");
    printf("│                                            │\n");
    printf("╰────────────────────────────────────────────╯\n");
    *router = getNumChar() - '0';
}

void viewQuestionEditor(LinkedList *list, Question *q, int new)
{
    for (;;)
    {
        if (new)
        {
            printf("╭────────────────────────────────────────────╮\n");
            printf("│  正在新增：%s                         │\n", q->id);
            printf("╰────────────────────────────────────────────╯\n");
        }
        else
        {
            printf("╭────────────────────────────────────────────╮\n");
            printf("│  正在编辑：%s                         │\n", q->id);
            printf("╰────────────────────────────────────────────╯\n");
        }

        printQuestion(q);

        printf("╭────────────────────────────────────────────╮\n");
        printf("│  [edit <属性> <新值>] 更新指定属性         │\n", q->id);
        printf("│  [rm] 删除题目  [save] 保存                │\n", q->id);
        printf("│  [cancel] 取消                             │\n", q->id);
        printf("╰────────────────────────────────────────────╯\n");

        printf("$ ");

        char input[BUFFER_SIZE] = "";
        char command[10] = "";

        do
        {
            fgets(input, BUFFER_SIZE, stdin);
        } while (strcmp(input, "\n") == 0);

        sscanf(input, "%s", command);

        if (strcmp(command, "edit") == 0)
        {
            char property[50] = "";
            char value[BUFFER_SIZE] = "";

            sscanf(input, "%s %s %[^\n]", command, property, value);
            if (strcmp(property, "qDesc") == 0)
            {
                strcpy(q->qDesc, value);
            }
            else if (strcmp(property, "answer") == 0)
            {
                if (strcmp(value, "A") == 0)
                {
                    q->answer = A;
                }
                else if (strcmp(value, "B") == 0)
                {
                    q->answer = B;
                }
                else if (strcmp(value, "C") == 0)
                {
                    q->answer = C;
                }
                else if (strcmp(value, "D") == 0)
                {
                    q->answer = D;
                }
            }
            else if (strcmp(property, "aDesc") == 0)
            {
                strcpy(q->aDesc, value);
            }
            else if (strcmp(property, "bDesc") == 0)
            {
                strcpy(q->bDesc, value);
            }
            else if (strcmp(property, "cDesc") == 0)
            {
                strcpy(q->cDesc, value);
            }
            else if (strcmp(property, "dDesc") == 0)
            {
                strcpy(q->dDesc, value);
            }
            else if (strcmp(property, "difficulty") == 0)
            {
                if (strcmp(value, "easy") == 0)
                {
                    q->difficulty = Easy;
                }
                else if (strcmp(value, "normal") == 0)
                {
                    q->difficulty = Normal;
                }
                else if (strcmp(value, "hard") == 0)
                {
                    q->difficulty = Hard;
                }
            }
            else if (strcmp(property, "point") == 0)
            {
                strcpy(q->point, value);
            }
        }
        else if (strcmp(command, "rm") == 0)
        {
            removeQuestionByID(list, q->id);
            saveQuestionLib(list);
            break;
        }
        else if (strcmp(command, "save") == 0)
        {
            saveQuestionLib(list);
            break;
        }
        else if (strcmp(command, "cancel") == 0)
        {
            break;
        }
        else
        {
            printf("Error: 无效指令\n");
        }
    }
}

void viewQuestionExplorer(int *router, int editor)
{
    printf("╭────────────────────────────────────────────╮\n");
    printf("│                  浏览题目                  │\n");
    printf("╰────────────────────────────────────────────╯\n");

    LinkedList *list = loadQuestionLib();

    printAllQuestionsShort(list);

    for (;;)
    {
        if (editor)
        {
            printf("╭────────────────────────────────────────────╮\n");
            printf("│  [0] 主菜单  [输入 ID] 编辑题目  [A] 列表  │\n");
            printf("│  [new] 新增题目                            │\n");
            printf("╰────────────────────────────────────────────╯\n");
        }
        else
        {
            printf("╭────────────────────────────────────────────╮\n");
            printf("│  [0] 主菜单  [输入 ID] 查看详情  [A] 列表  │\n");
            printf("╰────────────────────────────────────────────╯\n");
        }
        printf("$ ");

        char in[8];
        scanf("%s", in);

        if (strcmp(in, "0") == 0)
        {
            *router = VIEW_MAIN_MENU;
            break;
        }

        if (strcmp(in, "A") == 0)
        {
            printAllQuestionsShort(list);
            continue;
        }

        if (editor && strcmp(in, "new") == 0)
        {
            Question *new = createQuestion();
            generateId(new->id);
            strcpy(new->qDesc, "默认题目标题");
            strcpy(new->aDesc, "默认选项描述");
            strcpy(new->bDesc, "默认选项描述");
            strcpy(new->cDesc, "默认选项描述");
            strcpy(new->dDesc, "默认选项描述");
            strcpy(new->point, "默认知识点");
            new->answer = A;
            new->difficulty = Normal;

            llAppend(list, new);
            viewQuestionEditor(list, new, 1);
            return;
        }

        Question *ret = findQuestionByID(list, in);
        if (ret != NULL)
        {
            if (editor)
            {
                viewQuestionEditor(list, ret, 0);
                printAllQuestionsShort(list);
                return;
            }
            else
            {
                printQuestion(ret);
                continue;
            }
        }

        printf("Error: 无效指令\n");
    }

    freeQuestionList(list);
}

void viewRandomTest(int *router)
{
    printf("╭────────────────────────────────────────────╮\n");
    printf("│                  抽题作答                  │\n");
    printf("├────────────────────────────────────────────┤\n");
    printf("│  [0] 主菜单                                │\n");
    printf("├────────────────────────────────────────────┤\n");
    printf("│  输入题目要求：<题目数量> <难度> <知识点>  │\n");
    printf("╰────────────────────────────────────────────╯\n");

    printf("$ ");

    char input[BUFFER_SIZE] = "";
    char command[10] = "";

    do
    {
        fgets(input, BUFFER_SIZE, stdin);
    } while (strcmp(input, "\n") == 0);

    if (strcmp(input, "0\n") == 0)
    {
        *router = VIEW_MAIN_MENU;
        return;
    }

    char point[100];
    char difficulty[10];
    int num;

    sscanf(input, "%d %s %[^\n]", &num, difficulty, point);

    Difficulty diff;

    if (strcmp(difficulty, "easy") == 0)
    {
        diff = Easy;
    }
    else if (strcmp(difficulty, "normal") == 0)
    {
        diff = Normal;
    }
    else if (strcmp(difficulty, "hard") == 0)
    {
        diff = Hard;
    }

    Question *qs[MAX_LEN];
    int cur = 0;

    LinkedList *list = loadQuestionLib();

    for (size_t i = 0; i < llLen(list); i++)
    {
        Question *q = llGet(list, i);
        if (strcmp(q->point, point) == 0 && q->difficulty == diff)
        {
            qs[cur++] = q;
        }
    }

    for (size_t i = 0; i < cur; i++)
    {
        int index = rand() % cur;
        Question *temp = qs[index];
        qs[index] = qs[i];
        qs[i] = temp;
    }

    if (num == 0)
    {
        printf("Error: 题目数量不能为 0\n");
        return;
    }

    if (cur == 0)
    {
        printf("Error: 没有找到符合要求的题目");
        return;
    }

    if (cur < num)
    {
        printf("Error: 要求 %d 题，但是只找到了 %d 题\n", num, cur);
        return;
    }

    char ans[MAX_LEN] = "";

    for (size_t i = 0; i < num; i++)
    {
        clearConsole();
        printf("╭────────────────────────────────────────────╮\n");
        printf("│                   作答中                   │\n");
        printf("├────────────────────────────────────────────┤\n");
        printf("│      [Q] 上一题  [E] 下一题  [S] 提交      │\n");
        printf("╰────────────────────────────────────────────╯\n");
        printf("当前第 %d 题，共 %d 题\n\n", i + 1, num);
        printf("%s\n\n    [A] %s\n    [B] %s\n    [C] %s\n    [D] %s\n\n", qs[i]->qDesc, qs[i]->aDesc, qs[i]->bDesc, qs[i]->cDesc, qs[i]->dDesc);

        int submit = 0;

        for (;;)
        {
            printf("$ ");

            char in;
            do
            {
                scanf("%c", &in);
            } while (in == '\n');

            int outside = 0;

            if (in == 'Q')
            {
                if (i < 1)
                {
                    printf("Error: 已经是第一题\n");
                    continue;
                }

                i -= 2;
                break;
            }

            if (in == 'E')
            {
                if (i >= num - 1)
                {
                    printf("Error: 已经是最后一题\n");
                    continue;
                }

                break;
            }

            if (in == 'S')
            {
                submit = 1;
                break;
            }

            if (in >= 'A' && in <= 'D')
            {
                ans[i] = in;
                break;
            }

            printf("Error: 无效指令\n");
        }

        if (submit)
        {
            break;
        }
    }

    int correct = 0;

    for (size_t i = 0; i < num; i++)
    {
        if (ans[i] == 'A' + qs[i]->answer)
        {
            correct++;
        }
    }

    clearConsole();

    printf("╭────────────────────────────────────────────╮\n");
    printf("│                  作答结束                  │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("正确 %d 题，错误 %d 题，共 %d 题\n分数：%.1f\n\n[回车] 返回主菜单", correct, num - correct, num, 100 * (float)correct / num);

    getchar();
    getchar();

    *router = VIEW_MAIN_MENU;
}

#endif
