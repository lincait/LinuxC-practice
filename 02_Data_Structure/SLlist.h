#ifndef SLLIST_H_
#define SLLIST_H_

// 单向链表,无头
typedef struct llist
{
    int data;
    struct llist *next;
}Node;

int Llist_IndexAdd(Node **head, int data);   
void Llist_Output(Node *head);
Node *Llist_FindLast2(Node *head);
int LList_Resort(Node **head, int size);    
void LList_Delete(Node *head);


#endif 
