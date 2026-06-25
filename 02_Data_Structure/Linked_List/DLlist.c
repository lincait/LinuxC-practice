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
int DLlist_Add(DNode *head, Student *stu)
{
    if( DLlist_Find(head, stu->id) != NULL)
        return -2;  // 链表种已经存在该学生

    DNode *newnode = malloc(sizeof(DNode));
    if(newnode == NULL)
        return -1;
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

    return 0;
}

// 根据学号查找
DNode *DLlist_Find(DNode *head, char *id)
{
    DNode *cur = head->next;

    // 还没找到且没找完一圈, (cur != head)要先写，否则空链表时还会去比较一次
    while ( (cur != head) && (strcmp(cur->stu.id, id) != 0) )
    {
        cur = cur->next;
    }

    if(cur == head)
        return NULL;  //没找到
    else
        return cur;
}

// 根据学号删除对应学生
int DLlist_Delete(DNode *head, char *id)
{
    DNode *cur = DLlist_Find(head, id);

    if(cur == NULL)
        return -1;  //没找到
    else
    {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        free(cur);
        return 0;
    } 
}

// 根据学号查找学生，并修改其成绩
int DLlist_ChanegScore(DNode *head, char *id, float score)
{
    DNode *cur = DLlist_Find(head, id);

    if(cur == NULL)
        return -1;  //没找到
    else
    {
        cur->stu.score = score;
        return 0;
    } 
}

// 统计学生总数、最高分、最低分、平均分
void DLlist_OutStatistics(DNode *head)
{
    DNode *cur = head->next;
    float smax = cur->stu.score, smin = cur->stu.score, aver = 0;
    int num = 0;
    while (cur != head)
    {
        num ++;
        aver += cur->stu.score;

        if( smax < cur->stu.score )
            smax = cur->stu.score;
        if( smin > cur->stu.score )
            smin = cur->stu.score;
        cur = cur->next;
    }

    if(num == 0)
    {
        printf("链表为空\n");
        return ;
    }

    aver /= num;

    printf("总人数:%d\n",num);
    printf("最高分:%.2f\n",smax);
    printf("最低分:%.2f\n",smin);
    printf("平均分:%.2f\n",aver);
}

// 正向遍历
void DLlist_Output(DNode *head)
{
    DNode *cur = head->next;
    while (cur != head)
    {
        printf("%s\t%s\t%.2f\n",cur->stu.id,cur->stu.name,cur->stu.score);
        cur = cur->next;
    }
    
}

// 逆向遍历
void DLlist_OPOutput(DNode *head)
{
    DNode *cur = head->prev;
    while (cur != head)
    {
        printf("%s\t%s\t%.2f\n",cur->stu.id,cur->stu.name,cur->stu.score);
        cur = cur->prev;
    }
}

// 销毁整个链表释放空间
void DLlist_Destroy(DNode *head)
{
    DNode *cur = head->next;
    while (cur != head)
    {
        DNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(head);
}