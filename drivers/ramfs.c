#include "../include/fs.h"
#include <string.h>

#define MAX_FILES 64
#define MAX_FILE_SIZE 8192

typedef struct { 
    char name[64]; 
    char data[MAX_FILE_SIZE]; 
    int size; 
    int used; 
} rfile_t;

static rfile_t files[MAX_FILES];
static vfs_file_t open_table[MAX_FILES];

int ramfs_open(const char *path) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, path) == 0) {
            for (int j = 0; j < MAX_FILES; j++) {
                if (open_table[j].fd == 0) {
                    open_table[j].fd = j + 1;
                    open_table[j].pos = 0;
                    open_table[j].size = files[i].size;
                    open_table[j].backend = &files[i];
                    return open_table[j].fd;
                }
            }
        }
    }
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            strncpy(files[i].name, path, 63);
            files[i].used = 1;
            files[i].size = 0;
            for (int j = 0; j < MAX_FILES; j++) {
                if (open_table[j].fd == 0) {
                    open_table[j].fd = j + 1;
                    open_table[j].pos = 0;
                    open_table[j].size = 0;
                    open_table[j].backend = &files[i];
                    return open_table[j].fd;
                }
            }
        }
    }
    return -1;
}

static rfile_t* ramfs_get_rfile_by_fd(int fd) {
    if (fd <= 0 || fd > MAX_FILES) return NULL;
    vfs_file_t *vf = &open_table[fd - 1];
    if (vf->fd == 0) return NULL;
    return (rfile_t*)vf->backend;
}

int ramfs_read(int fd, char *buf, int len) {
    if (fd <= 0 || fd > MAX_FILES) return -1;
    vfs_file_t *vf = &open_table[fd - 1];
    if (vf->fd == 0) return -1;
    rfile_t *rf = (rfile_t*)vf->backend;
    int remain = rf->size - vf->pos;
    if (remain <= 0) return 0;
    int n = (len < remain) ? len : remain;
    memcpy(buf, rf->data + vf->pos, n);
    vf->pos += n;
    return n;
}

int ramfs_read_at(int fd, char *buf, int len, size_t offset) {
    if (fd <= 0 || fd > MAX_FILES) return -1;
    vfs_file_t *vf = &open_table[fd - 1];
    if (vf->fd == 0) return -1;
    rfile_t *rf = (rfile_t*)vf->backend;
    if (offset >= (size_t)rf->size) return 0;
    int remain = rf->size - offset;
    int n = (len < remain) ? len : remain;
    memcpy(buf, rf->data + offset, n);
    return n;
}

int ramfs_write(int fd, const char *buf, int len) {
    if (fd <= 0 || fd > MAX_FILES) return -1;
    vfs_file_t *vf = &open_table[fd - 1];
    if (vf->fd == 0) return -1;
    rfile_t *rf = (rfile_t*)vf->backend;
    int n = (len < MAX_FILE_SIZE) ? len : MAX_FILE_SIZE;
    memcpy(rf->data, buf, n);
    rf->size = n;
    vf->size = n;
    return n;
}

int ramfs_seek(int fd, size_t offset) {
    if (fd <= 0 || fd > MAX_FILES) return -1;
    vfs_file_t *vf = &open_table[fd - 1];
    if (vf->fd == 0) return -1;
    if (offset > (size_t)vf->size) return -1;
    vf->pos = offset;
    return 0;
}

int ramfs_close(int fd) {
    if (fd <= 0 || fd > MAX_FILES) return -1;
    vfs_file_t *vf = &open_table[fd - 1];
    if (vf->fd == 0) return -1;
    vf->fd = 0;
    vf->backend = NULL;
    vf->pos = 0;
    vf->size = 0;
    return 0;
}

int ramfs_preload(const char *path, const void *data, int len) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            strncpy(files[i].name, path, 63);
            files[i].used = 1;
            int n = (len < MAX_FILE_SIZE) ? len : MAX_FILE_SIZE;
            memcpy(files[i].data, data, n);
            files[i].size = n;
            return 0;
        }
    }
    return -1;
}

/* VFS wrappers */
int vfs_open(const char *path) { return ramfs_open(path); }
int vfs_read(int fd, char *buf, int len) { return ramfs_read(fd, buf, len); }
int vfs_read_at(int fd, char *buf, int len, size_t offset) { return ramfs_read_at(fd, buf, len, offset); }
int vfs_write(int fd, const char *buf, int len) { return ramfs_write(fd, buf, len); }
int vfs_seek(int fd, size_t offset) { return ramfs_seek(fd, offset); }
int vfs_close(int fd) { return ramfs_close(fd); }
int vfs_mount(void *fs) { (void)fs; return 0; }

