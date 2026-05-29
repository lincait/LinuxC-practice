#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 2
#define N 5

/*使用指针将一维数组逆序*/
void reverse(void)
{
    int a[N] = {10,11,12,13,14};
    int *p = a;
    int tmp;

    for (int i = 0; i < N / 2; i++)
    {
        //交换
        tmp = *(p + N-1 - i);
        *(p + N-1 - i) = *(p + i);
        *(p + i) = tmp;
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d\t",*(p + i));
    }
    printf("\n");
    
}

/*分别用行指针和列指针遍历输出二维数组所有元素*/
void out_r_c(void)
{
    int arr[M][N] = {{0,1,2,3,4},{10,11,12,13,14}};
    int (*r_p)[N] = arr;    //行指针
    int *c_p = arr[0];      //列指针

    printf("row out:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t",*(*(r_p+i) + j));     //一行一行输出
        }
        
    }
    printf("\n");

    printf("column out:\n");
    for (int i = 0; i < M * N; i++)
    {
        printf("%d\t",*(c_p + i));   //直接按顺序一个个输出   
    }
    printf("\n");
}

/*利用指针进行矩阵转置运算*/
void transpose(void)
{
    int matrix[M][N] = {{1,2,3,4,5},{6,7,8,9,20}};
    int matrix_T[N][M] = {0};
    int (*row_p)[N] = matrix;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix_T[j][i] = *(*(row_p+i) + j);
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%4d",matrix_T[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

/*创建字符串数组,对字符串按字典序排序（使用 strcmp），输出排序结果。*/
void sort_string(void)
{
    //每个元素都是const char *，指针指向的目标不能改，指向可以改
    const char *str[] = {"hello", "world", "c", "pointer"};     
    const char *tmp;
    int n = sizeof(str) / sizeof(str[0]);
    int k = 0;  //选择排序法用于记录当前较小数的下标

    for (int i = 0; i < n-1; i++)
    {
        k = i;
        for (int j = i+1; j < n; j++)
        {
            if(strcmp(str[k], str[j]) > 0)
            {
                k = j;
            }
        }

        if(k != i)
        {
            //本质上改的是指针的指向
            tmp = str[k];
            str[k] = str[i];
            str[i] = tmp;
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("%s\n",str[i]);
    }
    
}

int main(void)
{
    // reverse();
    // out_r_c();
    // transpose();
    sort_string();
    return 0;
}