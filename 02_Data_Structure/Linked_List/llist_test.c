#include <stdio.h>
#include <stdlib.h>

#include "SLlist.h"
#include "DLlist.h"

int main()
{
    // 单链表重排
    // Node *head = NULL;
    // for (int i = 6; i >= 1; i--)
    // {
    //     if(Llist_IndexAdd(&head, i) < 0)    // 小于0申请失败
    //         exit(0);     
    // }
    // Llist_Output(head);

    // if(LList_Resort(&head, 6) < 0)
    //     exit(0);
    // Llist_Output(head);

    // LList_Delete(head);

    // 双向链表学生系统
    DNode *head = NULL;
    Student stu[3] = {{"1001", "张三", 90},
                      {"1005", "七八", 91},
                      {"1002", "里斯", 10}};

    if(DLlist_Init(&head) < 0)
        exit(0);

    for (int i = 0; i < 3; i++)
    {
        DLlist_Add(head, &stu[i]); 
    }
    DLlist_Output(head);
    DLlist_OPOutput(head);

    DLlist_Delete(head, "1001");
    DLlist_ChanegScore(head, "1005", 68);
    DLlist_Output(head);

    DLlist_OutStatistics(head);
    DLlist_Destroy(head);

    
}