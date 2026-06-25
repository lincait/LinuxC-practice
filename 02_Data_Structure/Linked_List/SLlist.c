#include <stdlib.h>
#include <stdio.h>
#include "SLlist.h"

/*
给定一个单向链表（无头结点），节点数未知。请将其调整为“首、尾、次首、次尾……”交替取出的顺序。

举例：
输入：1 -> 2 -> 3 -> 4 -> 5
输出：1 -> 5 -> 2 -> 4 -> 3

输入：1 -> 2 -> 3 -> 4
输出：1 -> 4 -> 2 -> 3
*/

// 头插
int Llist_IndexAdd(Node **head, int data)
{
    // 创建新节点
    Node *newnode = (Node *)malloc(sizeof(Node));
    if(newnode == NULL)       // 申请失败
        return -1;
    newnode->data = data;

    newnode->next = (*head);
    (*head) = newnode;
    return 0;
}

void Llist_Output(Node *head)
{
    Node *cur;
    for (cur = head; cur != NULL; cur = cur->next)
    {
        printf("%d\t",cur->data);
    }
    printf("\n");
}

// 查找倒二个
Node *Llist_FindLast2(Node *head)
{
    Node *prev = NULL;
    Node *cur = head;

    if(head == NULL)
        return NULL;

    while (cur->next != NULL)
    {
        prev = cur;
        cur = cur->next;
    }
    
    return prev;
}

// 重排为：首、尾、次首、次尾
// size为链表长度
int LList_Resort(Node **head, int size)
{
    Node *llist = *head;
    Node *cur;

    if(*head == NULL)
        return -1;

    if(size % 2 == 0)
    {   
        while (llist->next->next != NULL)   // 偶数最后剩两个就不插了
        {
            // 找到最后一个并插入到第二个
            cur = Llist_FindLast2(llist);
            cur->next->next = llist->next;
            llist->next = cur->next;
            cur->next = NULL;

            llist = llist->next->next;  // 跳过一个
        }
    }
    else
    {
        while (llist->next != NULL)   // 奇数最后剩一个
        {
            cur = Llist_FindLast2(llist);
            cur->next->next = llist->next;
            llist->next = cur->next;
            cur->next = NULL;

            llist = llist->next->next;  
        }
    }
        
    return 0;
    
}

void LList_Delete(Node *head)
{
    Node *cur = head;
    while (cur != NULL)
    {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    
}