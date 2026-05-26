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

int main()
{
    // Buble_sort();
    // Select_sort();
    Prime_num();
    return 0;
}