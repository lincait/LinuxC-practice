#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

// 异常处理宏
#define CHECK(call, cmd)                            \
    do {                                            \
        if ((call) == -1) {                         \
            perror(cmd);                            \
            exit(EXIT_FAILURE);                     \
        }                                           \
    } while (0)

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("参数不符合要求：./client 地址 端口号\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;     // 客户端地址
    int res = 0;
    char readbuf[1024];
    char writebuf[1024];
    ssize_t read_bytes, write_bytes;

    // 要连接的服务端地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    res = inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    CHECK(res, "inet_pton");

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);    // 创建客户端套接字
    CHECK(client_fd, "socket");

    res = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 连接服务端
    CHECK(res, "connect");

    while(fgets(writebuf, sizeof(writebuf), stdin) != NULL)
    {
        write_bytes = send(client_fd, writebuf, sizeof(writebuf), 0);
        CHECK(write_bytes, "send");

        read_bytes = recv(client_fd, readbuf, sizeof(readbuf), 0);
        CHECK(read_bytes, "recv");
        printf("收到服务器的消息: %s\n", readbuf);
    }

    return 0;
}