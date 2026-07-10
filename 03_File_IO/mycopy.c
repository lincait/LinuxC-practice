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

    lseek(src_fd, offset, SEEK_SET);
    while((nbytes = read(src_fd, buf, sizeof(buf))) > 0)
    {
        write(obj_fd, buf, nbytes);
    }

    if(nbytes == -1)
        perror("read:");
        
    return 0;
}

// 输出文件全部内容
void Mycopy_Travel(const char *path)
{
    char buf[1024];
    FILE *fp = fopen(path, "r");
    while(fgets(buf, sizeof(buf), fp))
    {
        fprintf(stdout, "%s", buf);
    }

    fclose(fp);
}

// 输出文件大小（字节数）
off_t Mycopy_BytesCount(int fd)
{
    return lseek(fd, 0, SEEK_END);
}

// 输出文件的inode号和硬链接数
int Mycopy_Static(const char *path)
{
    struct stat data;
    stat(path, &data);

    fprintf(stdout, "inode:%ld\tnlink:%ld\n", data.st_ino, data.st_nlink);

    return 0;
}