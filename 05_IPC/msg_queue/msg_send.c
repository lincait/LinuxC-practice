#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

/*
    分别编写 sender.c 和 receiver.c，使用 POSIX 消息队列通信。
    消息格式:
    直接用字符串（字符数组），例如 char text[256]，优先级用整数。

    发送者 sender.c
    用 mq_open 打开已有的消息队列 "/myqueue"（只写方式，假设接收者已创建）。
    循环从键盘读取一行字符串（去掉换行）。
    若输入 "exit"，则发送内容 "exit" 且优先级设为 1，跳出循环。
    否则发送该字符串，优先级设为 0。
    关闭队列 mq_close。
*/

int main()
{
    // 打开消息队列
    int mq_fd = mq_open("/myqueue", O_WRONLY);
    if(mq_fd == -1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        // 从键盘接收消息，发送到消息队列
        char buf[256];
        fgets(buf, sizeof(buf), stdin);

        // 去掉末尾的换行符
        char *pos = strchr(buf, '\n');
        if(pos != NULL)
        *pos = '\0';

        // 接收到退出指令
        if(strcmp("exit", buf) == 0)
        {
            int res = mq_send(mq_fd, buf, strlen(buf)+1, 1);
            if(res == -1)
                perror("mq_send");
            break;
        }

        int res = mq_send(mq_fd, buf, strlen(buf)+1, 0);
        if(res == -1)
            perror("mq_send");

        memset(buf, 0, sizeof(buf));
    }

    mq_close(mq_fd);

    return 0;
}