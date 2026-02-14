#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>

void paging_init_identity(void);
void *create_page_directory(void);
int map_segment_to_vaddr(void *page_dir, void *phys, uint32_t vaddr, uint32_t size, uint32_t flags);
void switch_page_directory(void *page_dir);

#endif

