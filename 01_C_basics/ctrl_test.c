#include <stdio.h>
#include <stdlib.h>

/*
1.从终端输入数据，直到输入0为止，计算出其中的偶数的个数及平均值和奇数的个数及平均值
*/
static void test1(void)
{
    int input = 0;
    int ave_odd,ave_even;   //odd为奇
    int odd_c,even_c;
     
    do
    {
        printf("Please enter:");
        scanf("%d",&input);
        if(input % 2 == 1)
        {
            odd_c += 1;
            ave_odd += input;
        }
        else if(input % 2 == 0)
        {
            even_c += 1;
            ave_even += input;
        }
        else
        {
            printf("error\n");
        }
    }while (input != 0);

    printf("奇数个数:%d\t平均值:%d\n",odd_c,ave_odd);
    printf("偶数个数:%d\t平均值:%d\n",even_c,ave_even);
    
    return ;
}

/*
2.公鸡一只五块，母鸡一只三块，小鸡三只一块，100块买100只，公鸡母鸡小鸡各几只
*/
static void test2(void)
{
    int per_Roster = 5;
    int per_Hen = 3;
    int per3_chick = 1;

    int n_Roster,n_Hen,n_3chick;

    for(n_Roster = 0; n_Roster <= 100/per_Roster; n_Roster ++)
    {
        for(n_3chick = 0; n_3chick < (100-n_Roster)/3; n_3chick ++)
        {
            n_Hen = 100 - n_Roster - 3*n_3chick;
            if((n_Roster*per_Roster + n_Hen*per_Hen + n_3chick*per3_chick == 100) && n_Hen >= 0)
            {
                printf("Roster:%d\tHen:%d\t chick:%d\t\n",n_Roster,n_Hen,3*n_3chick);
            }
        }
    }
}

/*
3.输出1000以内所有质数
*/
static void test3(void)
{
    for(int i = 2; i < 1000; i ++)
    {
        for(int j = 2; j <= i; j ++)
        {
            if((i % j == 0) && (i != j))
                break;
            else if(i == j)
            {
                printf("%d\n",i);
            }

        }
    }
}

/*
4.在终端输出：
ABCDEF
BCDEF
CDEF
DEF
EF
F
*/
static void test4(void)
{
    char out1 = 'A'; 
    char out2 = 'A'; 
    for( ; out2 < 'G'; out2 ++)
    {
        for(out1 = out2; out1 < 'G'; out1 ++)
        {
            printf("%c",out1);
        }
        printf("\n");
    }
    
}

/*
5.从半径为1开始，输出圆的面积，直到面积大于100
*/
static void test5(void)
{
    float PI = 3.1415;
    for(int r = 1; PI*r*r <= 100; r ++)
    {
        printf("area is %f\n",PI*r*r);
    }
}


int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}