#ifndef DLLIST_H_
#define DLLIST_H_

#define MAXSIZE 10

typedef struct Student
{
    char id[MAXSIZE];
    char name[MAXSIZE];
    float score;
}Student;

// 双向链表
typedef struct DLlist
{
    Student stu;
    struct DLlist *prev;
    struct DLlist *next;
}DNode;

int DLlist_Init(DNode **head);
int DLlist_Add(DNode *head, Student *stu);
DNode *DLlist_Find(DNode *head, char *id);
int DLlist_Delete(DNode *head, char *id);
int DLlist_ChanegScore(DNode *head, char *id, float score);
void DLlist_Output(DNode *head);
void DLlist_OPOutput(DNode *head);
void DLlist_OutStatistics(DNode *head);
void DLlist_Destroy(DNode *head);


#endif