#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

/*
    场景：
    父进程创建一块 POSIX 共享内存，fork 出一个子进程。子进程读取一个文本文件，统计总行数和字符数，
    把结果写到共享内存里，然后退出。父进程等子进程结束后，从共享内存读出结果并打印。
    
    功能要求：
    父进程用 shm_open 创建共享内存对象，用 ftruncate 设定大小，用 mmap 映射到内存。
    父进程 fork 出一个子进程，子进程继承这块共享内存的映射。
    子进程做的事：用文件 I/O（open、read）读取一个文本文件（如 input.txt）；
    统计总行数和总字符数；
    把结果写入共享内存；
    退出（exit 或 return）。

    父进程做的事：用 waitpid 等待子进程结束；
    从共享内存读出行数和字符数，打印出来；
    解除映射（munmap）、删除共享内存对象（shm_unlink）、关闭 fd（close）。
*/

// 数据结构体，存在共享内存上，因此它的大小即为共享内存大小’
typedef struct {
    int line_count;  // 读到的行数
    int char_count;  // 读到的字符数
} result_t;

int main()
{
    
    char *map_p;    // 映射空间的起始地址
    char *shmname = "/myshm";
    int shm_size = sizeof(result_t);

    // 创建共享内存
    int shm_fd = shm_open(shmname, O_RDWR | O_CREAT, 0664);
    if(shm_fd < 0)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    int res = ftruncate(shm_fd, shm_size);
    if(res < 0)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // 内存映射到虚拟空间
    map_p = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(map_p == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    close(shm_fd);

    // 创建子进程
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        // 子进程继承了父进程的映射
        // 打开文件并统计
        char buf[128];     // 存放读出的数据
        ssize_t nbytes;      // read返回的值
        result_t res_data = {0,0};
        int fd = open("./input.txt", O_RDONLY);
        if(fd < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // 循环读取整个文件，避免文件大小超出buf的128部分读不到
        // 全部读完之后还会再read一次，这次返回0
        while((nbytes = read(fd, buf, sizeof(buf))) > 0)
        {
            for (int i = 0; i < nbytes; i++)
            {
                if(buf[i] == '\n')
                    res_data.line_count ++;
            }

            res_data.char_count += nbytes; 
        }
        if(nbytes < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // 若最后一个字节不是换行，说明前面没把最后一行算进去
        if((res_data.char_count > 0) && (buf[res_data.char_count - 1] != '\n'))
            res_data.line_count ++;

        // 数据放入虚拟空间，同时会同步改变物理上的共享内存
        result_t *res = (result_t *)map_p;  // 让结构体指针指向映射空间
        res->line_count = res_data.line_count;
        res->char_count = res_data.char_count;

        close(fd);
        munmap(map_p, shm_size);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // 阻塞等待子进程结束
        int sta;
        if(waitpid(pid, &sta, 0) < 0)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        // 读出共享内存里的数据
        printf("行数:%d\n字符数:%d\n", ((result_t *)map_p)->line_count, ((result_t *)map_p)->char_count);

        shm_unlink(shmname);
        munmap(map_p, shm_size);
    }

    return 0;
}