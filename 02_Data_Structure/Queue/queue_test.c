#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int main()
{
    int operate = 0;
    char next_p[QUE_MAXSIZE], cur_p[QUE_MAXSIZE];
    queue *patient_que;
    patient_que = Queue_Init();
    if(patient_que == NULL) // 申请失败
    {
        printf("内存申请失败\n");
        exit(0);
    }
        
    while (1)
    {
        printf("do what(Add:1\tCall:2\tShow Num:3\tShow Next:4\tShow All:5\texit:0):\n");
        scanf("%d", &operate);  // 未判断越界

        if(operate == 1)
        {
            printf("输入姓名:\n");
            scanf("%s", next_p);
            Queue_In(patient_que, next_p);
        }
        else if(operate == 2)
        {
            Queue_Out(patient_que, cur_p);
        }
        else if(operate == 3)
        {
            printf("排队人数：%d\n",Queue_ShowNum(patient_que));
        }
        else if(operate == 4)
        {
            printf("下一位：%s\n", Queue_ShowFront(patient_que));
        }
        else if(operate == 5)
        {
            Queue_Travel(patient_que);
        }
        else
            break;
    }

    Queue_Destroy(patient_que);

    return 0;
}