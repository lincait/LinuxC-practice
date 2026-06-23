#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLlist.h"

/*
学生管理系统（双向链表实现）
功能1：按学号顺序添加学生
功能2：根据学号删除学生
功能3：根据学号找到学生并修改成绩。
功能4：根据学号查找学生。
功能6：统计信息
*/

//初始化双向环链
int DLlist_Init(DNode **head)
{
    // 要修改头指针的指向，传二级指针
    *head = (DNode *)malloc(sizeof(DNode));
    if((*head) == NULL)
        return -1;

    strcpy((*head)->stu.id, "0");
    strcpy((*head)->stu.name, "0");
    (*head)->stu.score = 0;

    (*head)->prev = *head;
    (*head)->next = *head;

    return 0;
}

// 按照学号顺序插入
void DLlist_Add(DNode *head, Student *stu)
{
    DNode *newnode = malloc(sizeof(DNode));
    newnode->prev = NULL;
    newnode->next = NULL;
    newnode->stu = *stu;

    DNode *cur = head->next;
    while( (cur != head) && strcmp(cur->stu.id, newnode->stu.id)<0 )
    {
        cur = cur->next;
    }

    newnode->prev = cur->prev;
    newnode->next = cur;
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
}

// 根据学号删除对应学生
void DLlist_Delete(DNode *head, char *id)
{

}

void DLlist_Output(DNode *head)
{
    DNode *cur = head->next;
    do
    {
        printf("%s\t%s\t%d\n",cur->stu.id,cur->stu.name,cur->stu.score);
        cur = cur->next;
    } while (cur != head);
    
}