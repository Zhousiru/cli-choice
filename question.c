#ifndef QUESTION_C
#define QUESTION_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.c"

#define MAX_LEN 500
#define BUFFER_SIZE 5000

typedef enum
{
    A,
    B,
    C,
    D
} Answer;

typedef enum
{
    Easy,
    Normal,
    Hard,
} Diffculty;

typedef struct
{
    char id[8];
    char qDesc[MAX_LEN];
    Answer answer;
    char aDesc[MAX_LEN];
    char bDesc[MAX_LEN];
    char cDesc[MAX_LEN];
    char dDesc[MAX_LEN];
    Diffculty diffculty;
    char point[MAX_LEN];
} Question;

LinkedList *loadQuestionLib()
{
    FILE *fp = fopen("./data/questions.txt", "r");

    char buffer[BUFFER_SIZE];
    LinkedList *list = llCreate();

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    {
        char *token = strtok(buffer, "|");
        Question *q = (Question *)malloc(sizeof(Question));

        strcpy(q->id, token);
        token = strtok(NULL, "|");
        strcpy(q->qDesc, token);
        token = strtok(NULL, "|");
        q->answer = (Answer)atoi(token);
        token = strtok(NULL, "|");
        strcpy(q->aDesc, token);
        token = strtok(NULL, "|");
        strcpy(q->bDesc, token);
        token = strtok(NULL, "|");
        strcpy(q->cDesc, token);
        token = strtok(NULL, "|");
        strcpy(q->dDesc, token);
        token = strtok(NULL, "|");
        q->diffculty = (Diffculty)atoi(token);
        token = strtok(NULL, "|");
        if (token[strlen(token) - 1] == '\n')
        {
            // 去除 `\n`
            token[strlen(token) - 1] = '\0';
        }
        strcpy(q->point, token);

        llAppend(list, q);
    }

    return list;
}

void saveQuestionLib(LinkedList *list)
{
    FILE *fp = fopen("./data/questions.txt", "w+");

    for (size_t i = 0; i < llLen(list); i++)
    {
        Question *q = (Question *)llGet(list, i);

        char buffer[BUFFER_SIZE];
        sprintf(buffer, "%s|%s|%d|%s|%s|%s|%s|%d|%s\n",
                q->id, q->qDesc, q->answer, q->aDesc, q->bDesc,
                q->cDesc, q->dDesc, q->diffculty, q->point);

        fputs(buffer, fp);
    }

    fclose(fp);
}

Question *createQuestion()
{
    return (Question *)malloc(sizeof(Question));
}

void appendQuestionToList(LinkedList *list, Question *q)
{
    llAppend(list, q);
}

int removeQuestionByID(LinkedList *list, char *id)
{
    for (size_t i = 0; i < llLen(list); i++)
    {
        Question *q = (Question *)llGet(list, i);
        if (strcmp(q->id, id) == 0)
        {
            llRemove(list, i);
            return 0;
        }
    }

    return 1;
}

void freeQuestionList(LinkedList *list)
{
    for (size_t i = 0; i < llLen(list); i++)
    {
        llRemove(list, i);
    }
    free(list);
}

Question *findQuestionByID(LinkedList *list, char *id)
{
    for (size_t i = 0; i < llLen(list); i++)
    {
        Question *q = (Question *)llGet(list, i);
        if (strcmp(q->id, id) == 0)
        {
            return q;
        }
    }

    return NULL;
}

void generateId(char *id)
{
    size_t i;
    for (i = 0; i < 7; i++)
    {
        int r = rand() % 16;
        if (r < 10)
        {
            id[i] = '0' + r;
        }
        else
        {
            id[i] = 'a' + (r - 10);
        }
    }
    id[7] = '\0';
}

void printQuestion(Question *q)
{
    printf("编号：%s\n", q->id);
    printf("题目描述：%s\n", q->qDesc);
    printf("难度：");
    switch (q->diffculty)
    {
    case Easy:
        printf("简单\n");
        break;
    case Normal:
        printf("普通\n");
        break;
    case Hard:
        printf("困难\n");
        break;
    }
    printf("选项 A：%s\n", q->aDesc);
    printf("选项 B：%s\n", q->bDesc);
    printf("选项 C：%s\n", q->cDesc);
    printf("选项 D：%s\n", q->dDesc);
    printf("正确选项：");
    switch (q->answer)
    {
    case A:
        printf("A\n");
        break;
    case B:
        printf("B\n");
        break;
    case C:
        printf("C\n");
        break;
    case D:
        printf("D\n");
        break;
    }
    printf("知识点：%s\n", q->point);
}

void printAllQuestions(LinkedList *list)
{
    for (size_t i = 0; i < llLen(list) - 1; i++)
    {
        Question *q = (Question *)llGet(list, i);
        printQuestion(q);
        printf("--------------------\n");
    }
    printQuestion((Question *)llGet(list, llLen(list) - 1));
}

void printAllQuestionsShort(LinkedList *list)
{
    for (size_t i = 0; i < llLen(list); i++)
    {
        Question *q = llGet(list, i);
        printf("[%s] %s\t> %s\n", q->id, q->point, q->qDesc);
    }
}

#endif
