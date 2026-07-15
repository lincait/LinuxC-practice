#include "process_hde.h"

// 启动子进程，传入的结构体用于接收该子进程的信息
void start_process(child_t *p)
{
    int pid = fork();

    if(pid < 0)     //创建子进程异常
    {
        perror("fork");
    }
    else if(pid == 0)   // 子进程
    {
        int res = execve(p->args[0], p->args, NULL);
        if(res == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else    // 父进程
    {
        p->pid = pid;
        p->finished = RUNNING;
        printf("父进程%d启动子进程%d\n", getpid(), pid);
    }
}

// 父进程接收指定子进程,没有结束的进程不运行
void read_process(int pid, int status)
{
    // 查找是哪个子进程结束
    for(int i = 0; i < PROCESS_NUM; i ++)
    {
        // 找到结束的子进程信息结构体
        if(pid == subPro[i].pid && subPro[i].finished == RUNNING) 
        {
            subPro[i].finished = END;
            if(WIFEXITED(status))    // 接收到的子进程正常退出
                printf("结束的子进程PID:%d\tCommand:%s\tEndStatus:%d\n",subPro[i].pid, subPro[i].cmd, WEXITSTATUS(status));
            else    // 非正常退出，退出码设为-1
                printf("结束的子进程PID:%d\tCommand:%s\tEndStatus:%d\n",subPro[i].pid, subPro[i].cmd, -1);
        }
    }
 
}

// 打印所有存活子进程的信息
void print_process()
{
    for(int i = 0; i < PROCESS_NUM; i ++)
    {
        // 找到存活的子进程信息结构体
        if(subPro[i].finished == RUNNING) 
        {
                printf("存活的子进程PID:%d\tCommand:%s\n",subPro[i].pid, subPro[i].cmd);
        }
    }
}
