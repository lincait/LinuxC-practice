#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "process_hde.h"

/*
    父进程创建 3 个子进程，分别执行以下命令：
    ls -l /tmp（正常执行，返回 0）
    sleep 5（5 秒后正常退出）
    sh -c "exit 3"（立即退出，返回码 3）

    父进程需要：
    启动这 3 个子进程后，进入一个循环，每隔 1 秒调用一次 waitpid(-1, &status, WNOHANG) 非阻塞地检查是否有子进程结束。
    当某个子进程结束时，打印它的 PID、命令名、退出状态（如果是正常退出，打印退出码；如果被信号终止，打印信号编号）。
    一旦所有子进程都结束，父进程退出循环，并打印“所有子进程已结束”。
    在循环中，每 1 秒打印一次当前还存活的子进程 PID 和命令（方便观察）。
*/

child_t subPro[PROCESS_NUM];

int main(int argc, char const *argv[])
{
    int subStatus;  // 用于回收子进程状态
    int subpid;     // 用于接收子进程pid

    // 初始化每个子进程的信息
    subPro[0].pid = 0;
    subPro[0].cmd = "ls -l /tmp";
    subPro[0].args = (char *[]){"/usr/bin/ls", "-l", "/tmp", NULL};
    subPro[0].finished = 1;

    subPro[1].pid = 0;
    subPro[1].cmd = "sleep 5";
    subPro[1].args = (char *[]){"/usr/bin/sleep", "5", NULL};
    subPro[1].finished = 1;

    subPro[2].pid = 0;
    subPro[2].cmd = "sh -c \"exit 3\"";
    subPro[2].args = (char *[]){"/usr/bin/sh", "-c", "exit 3", NULL};
    subPro[2].finished = 1;

    // 父进程启动每个子进程
    start_process(&subPro[0]);
    start_process(&subPro[1]);
    start_process(&subPro[2]);

    //若exec执行成功，子进程不会执行下面的代码
    while (1)
    {
        // 非阻塞轮询所有子进程
        while( (subpid = waitpid(-1, &subStatus, WNOHANG)) > 0 )
        {
            if(subpid == -1)    // 调用出错
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            read_process(subpid, subStatus);
        }
        print_process();
        // 所有子进程结束
        if(subPro[0].finished == END && subPro[1].finished == END && subPro[2].finished == END)
        {
            printf("所有子进程结束\n");
            break;
        }
        sleep(1);
    }
    
    return 0;
    
}