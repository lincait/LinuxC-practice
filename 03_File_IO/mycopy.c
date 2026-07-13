#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mycopy.h"

// 拷贝文件
// 成功返回0
int Mycopy_Cpfile(const int src_fd, const int obj_fd, off_t offset)
{
    char buf[1024];
    int nbytes;

    int res = lseek(src_fd, offset, SEEK_SET);
    if(res == -1) return -1;

    while((nbytes = read(src_fd, buf, sizeof(buf))) > 0)
    {
        write(obj_fd, buf, nbytes);
    }

    if(nbytes == -1)
        return -2;
        
    return 0;
}

// 输出文件全部内容
int Mycopy_Travel(const char *path)
{
    char buf[1024];
    FILE *fp = fopen(path, "r");
    if(fp == NULL)  return -1;
    while(fgets(buf, sizeof(buf), fp))
    {
        fprintf(stdout, "%s", buf);
    }

    fclose(fp);
    return 0;
}

// 输出文件大小（字节数）
off_t Mycopy_BytesCount(int fd)
{
    return lseek(fd, 0, SEEK_END);
}

// 输出文件的inode号和硬链接数
int Mycopy_Statis(const char *path)
{
    struct stat data;
    int res = stat(path, &data);
    if(res == -1) return -1;

    fprintf(stdout, "inode:%ld\tnlink:%ld\n", data.st_ino, data.st_nlink);

    return 0;
}