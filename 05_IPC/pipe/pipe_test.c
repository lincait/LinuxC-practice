#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    编写一个程序，实现：
    父进程创建匿名管道。
    fork() 出子进程。
    父进程通过管道写端发送字符串 "hello, pipe!"，子进程从管道读端接收。
    子进程将字符串中的小写字母全转为大写，并打印。
    正确关闭父子进程各自不用的管道端（父写子读 → 父关读端，子关写端）。
*/

int main()
{
    int pipefd[2];
    int res = pipe(pipefd);     // 父进程创建管道
    char data[20] = {"hello, pipe!"};
    pid_t pid = fork(); 

    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        // 子进程执行，父进程不执行
        close(pipefd[1]);   // 读端先关闭写
        char buf[20];
        ssize_t bytes = read(pipefd[0], buf, sizeof(buf));
        if(bytes < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);   // 读完关闭读

        // 转换为大写 
        int offset = 'a' - 'A';
        for (int i = 0; i < bytes; i++)
        {
            if(buf[i] >= 'a' && buf[i] <= 'z')
            {
                buf[i] = buf[i] - offset;
            }  
        }
        printf("%s\n", buf);
    }
    else
    {
        // 父进程执行，子进程不执行
        close(pipefd[0]);   // 写端先关闭读
        ssize_t res = write(pipefd[1], data, strlen(data)+1);
        if(res < 0)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);   // 写完关闭写
    }
    
    return 0;
}