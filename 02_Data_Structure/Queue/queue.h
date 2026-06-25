#ifndef QUEUE_H__
#define QUEUE_H__

#define QUE_MAXSIZE  10
#define NAME_LEN     20

typedef struct sqqueue
{
    char patient[QUE_MAXSIZE][NAME_LEN];    // 存储病人
    int front;
    int rear;
}queue;

queue *Queue_Init();
int Queue_IsEmpty(queue *qu);
int Queue_IsFull(queue *qu);
int Queue_In(queue *qu, char *patient);
int Queue_Out(queue *qu, char *patient);
int Queue_ShowNum(queue *qu);
char *Queue_ShowFront(queue *qu);
int Queue_Travel(queue *qu);
void Queue_Destroy(queue *qu);

#endif