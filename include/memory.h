#ifndef MEMORY_H
#define MEMORY_H
#include <stddef.h>
void *kmalloc(size_t n);
void kfree(void *p);
void *kalloc_pages(size_t pages);
#endif

