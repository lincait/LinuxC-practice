#include "thread.h"

// 线程池中的工作线程
void Work_Thread(gpointer data, gpointer user_data)
{
    int value = ((task_t *)data)->value;   // 转换类型并取值
    int isprime = 1;    // 是素数为1，合数为0
    
    // 判断是否是素数
    for (size_t i = 2; i < value; i++)
    {
        if(value % i == 0)  // 为合数
        {
            isprime = 0;
            break;
        }
    }
    if(value == 1)  isprime = 0;    // 1不是素数

    g_usleep(200000);     // 模拟处理耗时
    
    // 统计信息
    pthread_mutex_lock(&mutex);     // 获取锁，避免其他线程对统计变量访问
    K ++;   // 已完成任务数加一
    sum += value;   // 数值总和
    if(isprime == 0)    // 合数
    {
        printf("[工作者] 完成任务 value=%d, 判定为非素数, 进度 %d/%d\n", value, K, TASKNUM);
    }
    else
    {
        prime[value] = value;
        prime_num ++;
        printf("[工作者] 完成任务 value=%d, 判定为素数, 进度 %d/%d\n", value, K, TASKNUM);
    }

    if(K == TASKNUM) // 全部任务都已经完成，通知主线程
    {
        pthread_cond_signal(&end_cond);  // 唤醒正在等待该条件的线程
    }
    pthread_mutex_unlock(&mutex);   // 释放锁
    sem_post(&inflight);    // 执行完一个任务把信号量加1，表示可以多推一个任务进来了
    free(data);     // 释放掉堆上存放的任务结构体
}

// 生产者线程 P1, 生产2, 4, 6, ..., 16 共 8 个任务
void *Producer1_Thread(void *)
{
    // 循环生成任务并推入线程池的任务队列
    for (int i = 0; i < TASKNUM / 2; i ++)
    {
        // 初始化任务参数
        // 把数据放在堆上，因为后面要把数据推入任务队列，要确保数据的生命周期全局有效
        task_t *task = (task_t *)malloc(sizeof(task_t));    
        task->producer_id = 1;
        task->value = 2 + 2 * i;

        sem_wait(&inflight);    // 占用一份资源，进行推送
        g_thread_pool_push(thread_pool, task, NULL);
        printf("[生产者%d] 生产任务 value=%d\n", task->producer_id, task->value);
        g_usleep(100000);
    }

    return NULL;
}

// 生产者线程 P2
void *Producer2_Thread(void *)
{
    // 循环生成任务并推入线程池的任务队列
    for (int i = 0; i < TASKNUM / 2; i ++)
    {
        // 初始化任务参数
        // 把数据放在堆上，因为后面要把数据推入任务队列，要确保数据的生命周期全局有效
        task_t *task = (task_t *)malloc(sizeof(task_t));    
        task->producer_id = 2;
        task->value = 1 + 2 * i;

        sem_wait(&inflight);    // 占用一份资源，进行推送
        g_thread_pool_push(thread_pool, task, NULL);
        printf("[生产者%d] 生产任务 value=%d\n", task->producer_id, task->value);
        g_usleep(100000);
    }

    return NULL;
}