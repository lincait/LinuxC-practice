#ifndef PROCESS_HDE__
#define PROCESS_HDE__

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROCESS_NUM 3
#define RUNNING 0
#define END 1

// 用于记录一个子进程的信息
typedef struct child_process{
    pid_t pid;
    char *cmd;
    char **args;
    int finished;   // 0=运行中, 1=已结束
} child_t;

extern child_t subPro[PROCESS_NUM];

void start_process(child_t *p);
void read_process(int pid, int status);
void print_process();

#endif