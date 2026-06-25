#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/*
模拟浏览器访问网页和返回功能。
*/

// 初始化栈
stack *Stack_Init()
{
    stack *st = malloc(sizeof(stack));
    if(st == NULL)
    {
        printf("申请失败\n");
        return NULL;
    }
    st->top = -1;   // 表示栈空
    return st;
}

// 入栈
void Stack_Push(stack *st, char *site)
{
    if( st->top == ST_MAXSIZE-1 )
    {
        printf("栈满\n");
        exit(1);
    }

    strcpy(st->site[++ st->top], site);
}

// 出栈
void Stack_Pop(stack *st, char *site)
{
    if( st->top == -1 )
    {
        printf("栈空\n");
        exit(1);
    }
    
    strcpy(site, st->site[st->top --]);
}

// 查看栈顶
char *Stack_Top(stack *st)
{
    if( st->top == -1 )
    {
        printf("栈空\n");
        exit(1);
    }

    return st->site[st->top];
}

// 遍历栈
void Stack_Travel(stack *st)
{
    if( st->top == -1 )
    {
        printf("栈空\n");
        exit(1);
    }

    for (int i = 0; i <= st->top; i++)
    {
        printf("%s\n", st->site[i]);
    }
}

// 销毁栈
void Stack_Destroy(stack *st)
{
    free(st);
}