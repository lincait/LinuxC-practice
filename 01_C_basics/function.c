#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pillar1 = 'A';
char pillar2 = 'B';
char pillar3 = 'C';
char tmp;


void hanoi(int n, char from, char to, char aux);
void filter_string(char *str, int (*predicate)(int));
int is_digit(int c);
int is_alpha(int c);

int main(void)
{
    //汉诺塔
    // hanoi(3, 'A', 'C', 'B');

    //函数指针实现的字符串过滤器
    char str[] = "ahsbf123";
    printf("%s\n",str);
    filter_string(str,is_alpha);
    printf("%s\n",str);

    return 0;
}

/*
函数指针实现的字符串过滤器
void filter_string(char *str, int (*predicate)(int));
从字符串 str 中原地删除所有使 predicate 返回 0 的字符。
另写两个辅助函数：
int is_digit(int c)：判断字符是否为数字（'0'~'9'）
int is_alpha(int c)：判断字符是否为英文字母
*/
void filter_string(char *str, int (*predicate)(int))
{
    int flag = 0;

    if(str == NULL || predicate == NULL) return ;

    int str_n = strlen(str);    //不会计算尾0,后续遍历时要多加一位
    
    for (int i = 0; i <= str_n; i++)
    {
        if(predicate(str[i]) == 0)  //函数返回值为0，需要过滤
        {
            flag = 1;   //进行了删除操作
            for (int j = i; j <= str_n; j++)
            {
                str[j] = str[j+1];
            }
            str_n --;
        }
        if(flag)    //进行了删除操作
        {
            flag = 0;
            i--;    //需要退回一位，避免遗漏
        }  
    }
}
int is_digit(int c) //判断字符是否为数字,是返回1
{
    return (c >= '0' && c <= '9');
}   
int is_alpha(int c) //判断字符是否为英文字母,是返回1
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
利用递归实现输出汉诺塔移动步骤
打印将 n 个盘子从柱 from 移到柱 to（借助辅助柱aux）的全部移动步骤。
每步格式：Move disk 1 from A to C（编号从上到下为 1~n）。
*/
void hanoi(int n, char from, char to, char aux)
{
    if(n == 0)
        return ;    //return掉当前层

    hanoi(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n",n, from, to);
    hanoi(n - 1, aux, to, from);
}