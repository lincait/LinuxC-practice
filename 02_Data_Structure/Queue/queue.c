#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/*
循环队列模拟医院窗口挂号。
*/ 

// 初始化队列
queue *Queue_Init()
{
    queue *que = malloc(sizeof(queue));
    if(que == NULL)
    {
        return NULL;
    }
    que->front = que->rear = 0;

    return que;
}

// 队列为空返回真
int Queue_IsEmpty(queue *qu)
{
    return qu->rear == qu->front;
}

// 队列为满返回真
int Queue_IsFull(queue *qu)
{
    return (qu->rear + 1) % QUE_MAXSIZE == qu->front;
}

// 入队
int Queue_In(queue *qu, char *patient)
{
    if(Queue_IsFull(qu))
        return -1;
    
    qu->rear = (qu->rear + 1) % QUE_MAXSIZE;
    strcpy(qu->patient[qu->rear], patient);

    return 0;
}

// 出队
int Queue_Out(queue *qu, char *patient)
{
    if(Queue_IsEmpty(qu))
        return -1;
    
    qu->front = (qu->front + 1) % QUE_MAXSIZE;
    strcpy(patient, qu->patient[qu->front]);

    return 0;
}

// 计算队中元素数量
int Queue_ShowNum(queue *qu)
{   
    if(Queue_IsEmpty(qu))
        return -1;

    int num = 0;
    num = (qu->rear - qu->front + QUE_MAXSIZE) % QUE_MAXSIZE;

    return num;
}

// 查看队首
char *Queue_ShowFront(queue *qu)
{
    if(Queue_IsEmpty(qu))
        return NULL;

    int cur = (qu->front + 1) % QUE_MAXSIZE;
    return qu->patient[cur];
}

// 遍历输出
int Queue_Travel(queue *qu)
{
    if(Queue_IsEmpty(qu))
        return -1;

    int i = qu->front;  
    while ( i != qu->rear )
    {
        i = (i + 1) % QUE_MAXSIZE;
        printf("%s\n", qu->patient[i]);
    }

    return 0;
}

void Queue_Destroy(queue *qu)
{
    free(qu);
}
