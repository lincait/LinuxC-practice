#ifndef STACK_H__
#define STACK_H__

#define ST_MAXSIZE  10
#define SITE_LEN    100

typedef struct sqstack
{
    char site[ST_MAXSIZE][SITE_LEN];    // 存储网站
    int top;
}stack;

stack *Stack_Init();
void Stack_Push(stack *st, char *site);
void Stack_Pop(stack *st, char *site);
char *Stack_Top(stack *st);
void Stack_Travel(stack *st);
void Stack_Destroy(stack *st);

#endif