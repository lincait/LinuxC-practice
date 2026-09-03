#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

/*
    题目：多客户端 TCP 回显服务器

    功能要求:
    服务端运行： ./server 8888
    客户端运行： ./client 127.0.0.1 8888
    客户端输入一行文字，服务端收到后原样返回
    请输入：hello
    服务器返回：hello
    客户端可以不断输入。按 Ctrl+D 结束输入并断开连接。

    服务端要求:
    按顺序使用 socket → bind → listen → accept
    主线程循环调用 accept()。
    每连接一个客户端，就创建一个线程处理该客户端。
    客户端线程不断：recv → 打印消息 → send回去
    recv() 返回 0，说明客户端断开，线程关闭对应套接字并结束。
    服务端打印客户端的 IP 和端口：
    客户端 127.0.0.1:52341 已连接
    收到 127.0.0.1:52341 的消息：hello
    客户端 127.0.0.1:52341 已断开
    
    客户端要求:
    使用 socket → connect
    使用 fgets()读取键盘输入。
    将输入发送给服务器。
    接收服务器返回的内容并打印。
    fgets() 返回 NULL 时，关闭套接字并退出。
    客户端按照“一次发送、等待回复、再发送下一次”的顺序工作，因此暂时不需要接收线程。

    验收方式:
    # 终端1 ./server 8888
    # 终端2 ./client 127.0.0.1 8888
    # 终端3 ./client 127.0.0.1 8888
    检查两个客户端是否都能独立发送消息并收到回显；其中一个退出后，另一个仍能继续使用。
*/

// 异常处理宏
#define CHECK(call, cmd)                            \
    do {                                            \
        if ((call) == -1) {                         \
            perror(cmd);                            \
            exit(EXIT_FAILURE);                     \
        }                                           \
    } while (0)
#define BACKLOG 10 

// 客户端信息结构体，传给处理客户端信息的线程
typedef struct 
{
    int client_fd;  
    struct sockaddr_in client_addr;
}client_info_t;

void *Deal_Client(void *data)
{
    client_info_t client_info = *(client_info_t *)data;     // 存下客户端信息
    free(data);     // 获取到客户端信息了，释放内存
    char *buf = malloc(sizeof(char) * 1024);
    if(buf == NULL) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ssize_t read_bytes, write_bytes;

    // recv返回0时退出循环
    while(read_bytes = recv(client_info.client_fd, buf, 1024, 0))
    {
        CHECK(read_bytes, "recv");
        printf("收到 %s:%d 的消息: %s\n", inet_ntoa(client_info.client_addr.sin_addr), ntohs(client_info.client_addr.sin_port), buf);

        // 将接收到的数据发回去
        write_bytes = send(client_info.client_fd, buf, read_bytes, 0);  
        CHECK(write_bytes, "send");
    }

    // 客户端断开
    printf("客户端%s:%d 已断开\n", inet_ntoa(client_info.client_addr.sin_addr), ntohs(client_info.client_addr.sin_port));
    free(buf);
    close(client_info.client_fd);
}

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("参数不符合要求：./server 端口号\n");
        exit(EXIT_FAILURE);
    }

    // 服务端和客户端地址
    struct sockaddr_in server_addr;
    client_info_t *client_info = malloc(sizeof(client_info_t));    // 该结构体要传给线程，所以放在堆上
    char *localhost = "127.0.0.1";      // 本地地址
    int res = 0;                        // 临时存储函数返回值
    socklen_t client_len = sizeof(client_info->client_addr); // 存储客户端地址大小

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&(client_info->client_addr), 0, sizeof(client_info->client_addr));

    // 获取服务端地址和端口号
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    res = inet_pton(AF_INET, localhost, &server_addr.sin_addr);
    CHECK(res, "inet_pton");

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);    // 创建套接字
    CHECK(listen_fd, "socket");

    res = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));    // 绑定地址
    CHECK(res, "bind");

    res = listen(listen_fd, BACKLOG);   // 监听
    CHECK(res, "listen");

    while(1)
    {
        client_info->client_fd = accept(listen_fd, (struct sockaddr *)&(client_info->client_addr), &client_len);    // 等待接收连接
        CHECK(client_info->client_fd, "accept");
        printf("客户端%s:%d 已连接\n", inet_ntoa(client_info->client_addr.sin_addr), ntohs(client_info->client_addr.sin_port));

        // 创建一个线程处理客户端的消息
        pthread_t pid_rw;
        if(pthread_create(&pid_rw, NULL, Deal_Client, client_info))
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        pthread_detach(pid_rw);
    }

    close(listen_fd);

    return 0;
}