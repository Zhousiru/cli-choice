#ifndef LINKEDLIST_C
#define LINKEDLIST_C

#include <stdlib.h>

// linkedList: 储存链表头尾指针等信息
struct linkedList
{
    struct linkedListNode *head; // 链表头指针
    struct linkedListNode *tail; // 链表尾指针
    size_t length;               // 链表长度
};

// linkedListNode: 链表节点
struct linkedListNode
{
    void *data;                  // 节点数据指针
    struct linkedListNode *next; // 指向下一节点的指针
};

// LinkedList: 链表结构体类型
typedef struct linkedList LinkedList;

// LinkedListNode: 链表节点结构体类型
typedef struct linkedListNode LinkedListNode;

/**
 * 创建链表
 *
 * @return 新建链表信息
 */
LinkedList *llCreate();

/**
 * 在链表尾部添加节点
 *
 * @param ll 指向链表信息的指针
 * @param data 节点数据的指针
 */
void llAppend(LinkedList *ll, void *data);

/**
 * 在指定位置后插入新节点
 *
 * @param ll 指向链表信息的指针
 * @param data 节点数据的指针
 * @param afterIndex 想要插入的位置
 */
void llInsert(LinkedList *ll, void *data, int afterIndex);

/**
 * 获取指定位置的节点
 *
 * @param ll 指向链表信息的指针
 * @param index 想要获取的位置
 * @return 指向节点数据的指针
 */
void *llGet(LinkedList *ll, size_t index);

/**
 * 移除指定位置的节点，释放对应数据内存
 *
 * @param ll 指向链表信息的指针
 * @param index 想要移除的位置
 */
void llRemove(LinkedList *ll, size_t index);

/**
 * 获取链表长度
 *
 * @param ll 指向链表信息的指针
 * @return 链表长度
 */
size_t llLen(LinkedList *ll);

LinkedList *llCreate()
{
    LinkedList *ll = (LinkedList *)malloc(sizeof(LinkedList));

    ll->head = NULL;
    ll->tail = NULL;
    ll->length = 0;

    return ll;
}

void llAppend(LinkedList *ll, void *data)
{
    LinkedListNode *llNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));

    llNode->data = data;
    llNode->next = NULL;

    if (ll->tail == NULL)
    {
        // 链表中没有任何元素
        ll->head = llNode;
        ll->tail = llNode;
        ll->length++;

        return;
    }

    ll->tail->next = llNode;
    ll->tail = llNode;
    ll->length++;
}

void llInsert(LinkedList *ll, void *data, int afterIndex)
{
    if (afterIndex == -1)
    {
        // 如果需要在链表头插入
        LinkedListNode *newNode = malloc(sizeof(LinkedListNode)); // 创建新节点
        newNode->data = data;
        newNode->next = ll->head;
        ll->head = newNode; // 更新头指针
        if (ll->tail == NULL)
        { // 如果链表为空，更新尾指针
            ll->tail = newNode;
        }
        ll->length++; // 更新链表长度
        return;
    }

    LinkedListNode *target = ll->head;
    for (size_t i = 0; i < afterIndex; i++)
    {
        target = target->next;
        if (target == NULL)
        {
            // `target` 不存在
            return;
        }
    }

    LinkedListNode *llNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    llNode->data = data;

    if (target == ll->tail)
    {
        // 在 `tail` 后插入，相当于 `append`
        llAppend(ll, data);

        return;
    }

    // `tail` 前插入
    llNode->next = target->next;
    target->next = llNode;
    ll->length++;
}

void *llGet(LinkedList *ll, size_t index)
{
    LinkedListNode *target = ll->head;
    for (size_t i = 0; i < index; i++)
    {
        target = target->next;
        if (target == NULL)
        {
            // `target` 不存在
            return NULL;
        }
    }

    return target->data;
}

void llRemove(LinkedList *ll, size_t index)
{
    if (index == 0)
    {
        // 删除 `head`，特殊处理
        LinkedListNode *target = ll->head;
        ll->head = target->next;

        free(target->data);
        free(target);
        ll->length--;

        return;
    }

    LinkedListNode *before = ll->head;
    for (size_t i = 0; i < index - 1; i++)
    {
        before = before->next;
        if (before == NULL)
        {
            // `target` 前面一个元素不存在
            return;
        }
    }

    LinkedListNode *target = before->next;
    if (target == NULL)
    {
        // `target` 不存在
        return;
    }

    LinkedListNode *after = target->next;
    if (after == NULL)
    {
        // 删除 `tail`，特殊处理
        before->next = NULL;
        ll->tail = before;

        free(target->data);
        free(target);
        ll->length--;

        return;
    }

    // `target` 为 `head` 和 `tail` 中间的一项
    before->next = after;

    free(target->data);
    free(target);
    ll->length--;
}

size_t llLen(LinkedList *ll)
{
    return ll->length;
}

#endif
