#include <stdio.h>
#include <stdlib.h>

#define N 10

/*冒泡排序*/
static void Buble_sort(void)
{
    int a[N] = {23,1,16,8,41,7,51,9,13,21};
    int temp;

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d  ",a[i]);
    }
    printf("\n");    
}

/*选择排序*/
static void Select_sort(void)
{
    int a[N] = {23,1,16,8,41,7,51,9,13,21};
    int temp;

    for (int i = 0; i < N - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < N; j++)
        {
            if(a[j] < a[k])
            {
                k = j;
            }
        }
        if(k != i)
        {
            temp = a[k];
            a[k] = a[i];
            a[i] = temp;
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d  ",a[i]);
    }
    printf("\n");    
}

/*删除法求1000以内质数*/
static void Prime_num(void)
{
    int a[1001] = {0};

    for(int i = 2; i <= 1000/2; i ++)
    {
        if(a[i] == 0)   //如果该位置没有被删
        {
            for (int j = i + 1; j <= 1000; j++)
            {
                if(j % i == 0)
                {
                    a[j] = -1;  //表示该位置被删
                }
            }
        }
    }

    for (int i = 2; i < 1001; i++)
    {
        if(a[i] == 0)
            printf("%d\n",i);
    }
    
}

/*求二维数组每行和、每列和、总和（不用额外变量存储）*/
static void Sum(void)
{
    //数据为4行3列，则创建5行4列数组，每行每列的最后一个存放对应和
    int a[5][4] = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a[4][3] += a[i][j]; //最后一个格子存放总和
            a[4][j] += a[i][j]; //最后一行依次分别加上当前行所在列（一次外层循环，每个列和分别加一次）
            a[i][3] += a[i][j]; //最后一列依次加上当前行全部列（一次外层循环算完一个行和）
        }
        
    }
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    
}

/*矩阵乘积*/
static void matri_mul(void)
{
    int a[3][4] = {{4,5,6,7},{3,1,1,1},{1,2,3,5}};
    int b[4][3] = {{0,0,0},{1,1,1},{2,2,2},{3,3,3}};
    int mul[3][3];  //a*b

    for(int i = 0; i < 3; i ++)         //每轮循环计算完mul的一行
    {
        for(int j = 0; j < 3; j ++)     //每轮循环计算完两个向量内积（一行乘一列）
        {
            for (int k = 0; k < 4; k++) //每轮循环计算两个元素乘积
            {
                mul[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    //显示输出结果
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d\t",mul[i][j]);
        }
        printf("\n");
    }

}

int main()
{
    // Buble_sort();
    // Select_sort();
    // Prime_num();
    // Sum();
    matri_mul();
    return 0;
}