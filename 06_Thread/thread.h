#ifndef THREAD_H__
#define THREAD_H__

#include <glib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORKTHREAD 2    // 线程池中同时工作的最大线程数
#define TASKNUM 16          // 需要执行的任务总数
#define INFLIGHT_NUM 4      // 正在执行以及正在排队的最大任务数量

extern sem_t inflight;
extern GThreadPool *thread_pool;
extern pthread_mutex_t mutex;
extern pthread_cond_t end_cond;
extern int K;  
extern int prime_num; 
extern int prime[TASKNUM];  
extern int sum;    

typedef struct {
    int producer_id;   // 生产者编号：1 或 2（用于日志 [生产者N]）
    int value;         // 任务数值：P1 生产 2~16 的偶数，P2 生产 1~15 的奇数
} task_t;

void Work_Thread(gpointer data, gpointer user_data);
void *Producer1_Thread(void *);
void *Producer2_Thread(void *);

#endif