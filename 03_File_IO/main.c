#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "mycopy.h"

/*
    实现内容：./mycopy <源文件> <目标文件> <偏移量>
    偏移量：是一个非负整数（单位：字节）。
    程序将源文件从偏移量位置开始的所有数据，复制到目标文件中。
    若目标文件已存在，则截断为0后写入；若不存在，则创建它。
    复制完成后，程序：
    再次打开目标文件，将其全部内容读出并打印到标准输出（使用标准C库）。
    输出目标文件的大小（字节数）。
    输出目标文件的 inode 号和硬链接数（通过 stat 系统调用）。
*/

int main(int argc, char const *argv[])
{
    // 命令不符号要求
    if(argc != 4)
    {
        printf("error\n<src_path> <obj_path> <offset>\n");
        exit(EXIT_FAILURE);
    }

    // 解析传入的参数
    const char *src_path = argv[1];
    const char *obj_path = argv[2];
    off_t offset = (off_t)atoll(argv[3]);

    // 打开文件
    int src_fd = open(src_path, O_RDONLY);
    off_t column = Mycopy_BytesCount(src_fd);
    if(offset>=column || offset<0)  
    {
        printf("offset not allow\n");
        exit(EXIT_FAILURE);
    }
    int obj_fd = open(obj_path, O_RDWR | O_TRUNC | O_CREAT, 0664);
    if(src_fd<0 || obj_fd<0)
    {
        perror("open:");
        exit(EXIT_FAILURE);
    }

    // 复制文件
    int res = Mycopy_Cpfile(src_fd, obj_fd, offset);
    if(res < 0)
        exit(EXIT_FAILURE);

    Mycopy_Travel(obj_path);
    printf("objfile column:%ld\n", Mycopy_BytesCount(obj_fd));
    Mycopy_Static(obj_path);

    close(src_fd);
    close(obj_fd);

    return 0;
}
