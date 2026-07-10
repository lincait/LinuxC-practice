#ifndef MYCOPY_H__
#define MYCOPY_H__

int Mycopy_Cpfile(const int src_fd, const int obj_fd, off_t offset);
void Mycopy_Travel(const char *path);
off_t Mycopy_BytesCount(int fd);
int Mycopy_Static(const char *path);

#endif