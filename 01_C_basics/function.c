#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char pillar1 = 'A';
char pillar2 = 'B';
char pillar3 = 'C';
char tmp;


void hanoi(int n, char from, char to, char aux);
void filter_string(char *str, int (*predicate)(int));
int is_digit(int c);
int is_alpha(int c);
int calculate(const char *expr);
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int divm(int a, int b);   

int main(void)
{
    //汉诺塔
    // hanoi(3, 'A', 'C', 'B');

    //函数指针实现的字符串过滤器
    // char str1[] = "a1b2c3d4e5f6g7";
    // printf("%s\n",str1);
    // filter_string(str1,is_digit);
    // printf("%s\n",str1);
    // char str2[] = "a1b2c3d4e5f6g7";
    // filter_string(str2,is_alpha);
    // printf("%s\n",str2);

    //用函数指针表驱动整型计算器（四则运算）
    char str[] = "46 * 23";
    printf("%d\n",calculate(str));


    return 0;
}

/*
用函数指针表驱动计算器（四则运算）
设计一个计算器，接收字符串输入，格式为 "a op b"（例如 "3 + 5"），支持操作：+、-、*、/。编写函数：
int calculate(const char *expr);
解析字符串并计算整数结果（舍去除法小数部分，向零方向）。
*/
int calculate(const char *expr)
{
    //函数指针数组，每个元素都指向一个函数
    int (*op_func[4])(int,int) = {add, sub, mul, divm};
    char op_char[4] = {'+','-','*','/'};
    char ch_num1[32],ch_num2[32];
    int num1=0,num2=0,res=0;
    int i = 0, m = 0;
    int op_idx = 0;

    //获取两个数据
    while (expr[i] != ' ')
    {
        ch_num1[i] = expr[i];
        i++;
    }
    op_idx = i+1;     //记录操作符的位置
    ch_num1[i] = '\0';     //建立一个字符串后一定要补\0
    for (int j = 0; ch_num1[j] != '\0'; j++)    //将字符串转为数
    {
        num1 = num1 * 10 + (ch_num1[j] - '0');
    }

    i += 3;     //定位到第二个数
    while (expr[i] != '\0')
    {
        ch_num2[m] = expr[i];
        m ++;
        i ++;
    }
    ch_num2[i] = '\0';
    for (int j = 0; ch_num2[j] != '\0'; j++)
    {
        num2 = num2 * 10 + (ch_num2[j] - '0');
    }

    //判断操作符，执行计算
    for (int j = 0; j < 4; j++)
    {
        if(expr[op_idx] == op_char[j])
        {
            res = op_func[j](num1,num2);
        }
    }
    
    return res;
    
}
int add(int a, int b)   { return a + b;}
int sub(int a, int b)   { return a - b;}
int mul(int a, int b)   { return a * b;}
int divm(int a, int b)
{
    if(b == 0) 
    {
        printf("除数为0!\n");
        return -1;
    }
    else
        return a / b;
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
    char *read;     //遍历每个字符
    char *write;    //保存需要保留的字符

    write = read = str;     //三个指针指向同一块内存，改一个其他一起改

    if(str == NULL || predicate == NULL) return ;

    while(*read)  //'\0'对应asc码为0
    {
        //返回值为1，需要保留
        if(predicate(*read))   
        {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0';
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