#include "../include/paging.h"
#include "../include/memory.h"
#include "../include/hal.h"
#include <stdint.h>
#include <string.h>

#define PAGE_SIZE 4096
#define PDE_COUNT 1024

static inline uint32_t pde_entry(uint32_t addr, uint32_t flags) { return (addr & 0xFFFFF000) | flags; }
static inline uint32_t pte_entry(uint32_t addr, uint32_t flags) { return (addr & 0xFFFFF000) | flags; }

void paging_init_identity(void) {
    void *pd = pfa_alloc_pages(1);
    if (!pd) return;
    memset(pd, 0, 4096);
    
    void *pt = pfa_alloc_pages(1);
    if (!pt) return;
    memset(pt, 0, 4096);
    
    for (int i = 0; i < 1024; i++) {
        ((uint32_t*)pt)[i] = pte_entry(i * 4096, 0x3);
    }
    
    ((uint32_t*)pd)[0] = pde_entry((uint32_t)(uintptr_t)pt, 0x3);
    
    asm volatile ("mov %0, %%cr3" :: "r"(pd));
    uint32_t cr0;
    asm volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile ("mov %0, %%cr0" :: "r"(cr0));
    hal_console_write("Paging enabled\n");
}

void *create_page_directory(void) {
    void *pd = pfa_alloc_pages(1);
    if (!pd) return NULL;
    memset(pd, 0, 4096);
    return pd;
}

int map_segment_to_vaddr(void *page_dir, void *phys, uint32_t vaddr, uint32_t size, uint32_t flags) {
    uint32_t p = (uint32_t)(uintptr_t)phys;
    uint32_t end = vaddr + size;
    
    for (uint32_t va = vaddr; va < end; va += PAGE_SIZE, p += PAGE_SIZE) {
        uint32_t pd_index = (va >> 22) & 0x3FF;
        uint32_t pt_index = (va >> 12) & 0x3FF;
        uint32_t *pd = (uint32_t*)page_dir;
        uint32_t pde = pd[pd_index];
        uint32_t *pt;
        
        if (!(pde & 1)) {
            pt = pfa_alloc_pages(1);
            if (!pt) return -1;
            memset(pt, 0, 4096);
            pd[pd_index] = pte_entry((uint32_t)(uintptr_t)pt, flags | 0x1);
        } else {
            pt = (uint32_t*)(uintptr_t)(pde & 0xFFFFF000);
        }
        pt[pt_index] = pte_entry(p, flags | 0x1);
    }
    return 0;
}

void switch_page_directory(void *page_dir) {
    asm volatile ("mov %0, %%cr3" :: "r"(page_dir));
}

