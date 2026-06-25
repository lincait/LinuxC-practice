#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int main()
{
    stack *website_his;
    int operate = 0;
    char cur_web[SITE_LEN],tmp[SITE_LEN];

    website_his = Stack_Init();
    while (1)
    {
        printf("do what(Enter:1, Back:2, Show cur:3, Show all:4, exit:5):\n");
        scanf("%d", &operate);

        if(operate == 1)
        {
            printf("Enter Website:\n");
            scanf("%s", cur_web);
            Stack_Push(website_his, cur_web);
        }
        else if(operate == 2)
        {
            Stack_Pop(website_his, tmp);
        }
        else if(operate == 3)
        {
            strcpy(cur_web, Stack_Top(website_his));
            printf("%s\n",cur_web);
        }
        else if(operate == 4)
        {
            Stack_Travel(website_his);
        }
        else
            break;
    }

    Stack_Destroy(website_his);
    
    return 0;
}