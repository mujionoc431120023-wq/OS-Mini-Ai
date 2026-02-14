#ifndef FS_H
#define FS_H
#include <stddef.h>

typedef struct vfs_file {
    int fd;
    size_t pos;
    size_t size;
    void *backend;
} vfs_file_t;

int vfs_mount(void *fs);
int vfs_open(const char *path);
int vfs_read(int fd, char *buf, int len);
int vfs_write(int fd, const char *buf, int len);
int vfs_close(int fd);
int vfs_read_at(int fd, char *buf, int len, size_t offset);
int vfs_seek(int fd, size_t offset);
int ramfs_open(const char *path);
int ramfs_read(int fd, char *buf, int len);
int ramfs_read_at(int fd, char *buf, int len, size_t offset);
int ramfs_write(int fd, const char *buf, int len);
int ramfs_seek(int fd, size_t offset);
int ramfs_close(int fd);
int ramfs_preload(const char *path, const void *data, int len);

#endif

