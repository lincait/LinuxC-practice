#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*动态整数数组的统计与变换
用 typedef 定义一个动态整型数组类型 Vector，并实现相关操作。底层使用动态分配的数组，容量不足时自动扩容。
结构定义：指向动态数组的指针、当前元素个数、已分配空间的容量（元素个数）
需要实现的函数：
void vector_init(Vector *v);                // 初始化（空数组，容量可为0或4）
void vector_push(Vector *v, int value);     // 尾部添加元素，容量不足时扩容为 2 倍
void vector_insert(Vector *v, size_t index, int value); // 在指定位置插入，后续元素后移
void vector_remove(Vector *v, size_t index); // 删除指定位置的元素，后续元素前移
int  vector_get(const Vector *v, size_t index); // 返回元素值，索引越界时打印错误并返回0
void vector_free(Vector *v);                // 释放 data 指向的内存，并将 size 和 capacity 置零
size_t vector_size(const Vector *v);        // 返回元素个数
要求：
所有内存操作必须手动管理。
扩容策略：首次添加时若容量为 0 则分配初始容量（如 4），之后每次容量不足时 realloc 为原容量的两倍。
插入/删除时，若索引越界则不操作并打印错误信息。
*/
typedef struct 
{
    int *data;      // 指向动态数组的指针
    size_t size;    // 当前元素个数
    size_t capacity;// 已分配空间的容量（能容纳元素个数）
}Vector;

void vector_init(Vector *v);                
void vector_push(Vector *v, int value);     
void vector_insert(Vector *v, size_t index, int value); 
void vector_remove(Vector *v, size_t index); // 删除指定位置的元素，后续元素前移
int  vector_get(const Vector *v, size_t index); // 返回元素值，索引越界时打印错误并返回0
void vector_free(Vector *v);                // 释放 data 指向的内存，并将 size 和 capacity 置零
size_t vector_size(const Vector *v);        // 返回元素个数
void vector_printf(const Vector *v);


int main()
{
    Vector d_arr;
    
    vector_init(&d_arr);
    vector_push(&d_arr,33);
    vector_push(&d_arr,139);
    vector_printf(&d_arr);

    free(d_arr.data);
    d_arr.data = NULL;


	return 0;
}

// 初始化（空数组，容量可为0或4）
void vector_init(Vector *v)
{   
    v->data = malloc(sizeof(int) * 4);
    v->size = 0;
    v->capacity = 4;

    if(v->data == NULL)
    {
        printf("申请内存失败\n");
        v->size = 0;
    }
}
// 尾部添加元素，容量不足时扩容为 2 倍
void vector_push(Vector *v, int value)
{
    int *tmp = NULL;
    size_t remain = v->capacity - v->size;  //剩余容量

    if(remain < 1) //容量不足，扩容
    {
        tmp = realloc(v->data,sizeof(int) * (v->capacity)*2);
        v->data = tmp;
        v->capacity *= 2;
    }
    else
    {
        v->data[v->size] = value;
        v->size ++;
    }
        
}
// 在指定位置插入，后续元素后移
void vector_insert(Vector *v, size_t index, int value)
{
    size_t remain = v->capacity - v->size;  //剩余容量
    if(remain < 1) //容量不足
    {
        printf("容量不足，越界！\n");
        return ;
    }

    for (int i = v->size-index; i >= index; i--)  //后移
    {
        v->data[i+1] = v->data[i];
    }

    v->data[index] = value;
    v->size ++;
    
}
void vector_remove(Vector *v, size_t index)
{

}
int  vector_get(const Vector *v, size_t index)
{

}
void vector_free(Vector *v)
{

}
size_t vector_size(const Vector *v)
{

}
//打印数组元素和信息
void vector_printf(const Vector *v)
{
    for (int i = 0; i < v->size; i++)
    {
        printf("%d\t",v->data[i]);
    }
    printf("\n");
}
