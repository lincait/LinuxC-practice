#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

/*
    接收者 receiver.c
    用 mq_open 创建消息队列 "/myqueue"（O_RDONLY | O_CREAT），设置队列属性：
    最大消息数 10（mq_maxmsg = 10）
    每条消息最大长度 256 字节（mq_msgsize = 256）
    循环用 mq_receive 接收消息（会按优先级从高到低获取）。
    打印收到的优先级和内容。
    若收到内容为 "exit"，跳出循环。
    调用 mq_close 关闭队列，再调用 mq_unlink 删除队列名。
*/

int main()
{
    // 创建消息队列
    struct mq_attr my_attr;
    my_attr.mq_maxmsg = 10;
    my_attr.mq_msgsize = 256;
    my_attr.mq_curmsgs = 0;
    my_attr.mq_flags = 0;

    int mq_fd = mq_open("/myqueue", O_RDONLY | O_CREAT, 0664, my_attr);
    if(mq_fd == -1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // 接收消息队列的消息
    while(1)
    {
        char buf[256];
        unsigned int level = 0;

        // 接收消息，出队
        memset(buf, 0, sizeof(buf));
        int res = mq_receive(mq_fd, buf, sizeof(buf), &level);
        if(res == -1)
            perror("mq_receive");

        printf("[prio=%d]%s\n", level, buf);
        if(strcmp("exit", buf) == 0)
            break;
    }

    mq_close(mq_fd);
    mq_unlink("/myqueue");

    return 0;
}