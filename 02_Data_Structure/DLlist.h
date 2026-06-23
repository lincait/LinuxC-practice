#ifndef DLLIST_H_
#define DLLIST_H_

#define MAXSIZE 10

typedef struct Student
{
    char id[MAXSIZE];
    char name[MAXSIZE];
    int score;
}Student;

// 双向链表
typedef struct DLlist
{
    Student stu;
    struct DLlist *prev;
    struct DLlist *next;
}DNode;

int DLlist_Init(DNode **head);
void DLlist_Add(DNode *head, Student *stu);
void DLlist_Delete(DNode *head, char *id);
void DLlist_Output(DNode *head);


#endif