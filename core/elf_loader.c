#include "../include/elf.h"
#include "../include/fs.h"
#include "../include/memory.h"
#include "../include/process.h"
#include "../include/paging.h"
#include "../include/hal.h"
#include <string.h>
#include <stdint.h>

#define PAGE_SIZE 4096
#define PAGE_ALIGN_DOWN(x) ((x) & ~(PAGE_SIZE-1))
#define PAGE_ALIGN_UP(x) (((x) + PAGE_SIZE - 1) & ~(PAGE_SIZE-1))

extern void *pfa_alloc_pages(uint32_t pages);
extern void *create_page_directory(void);
extern int map_segment_to_vaddr(void *page_dir, void *phys, uint32_t vaddr, uint32_t size, uint32_t flags);

int load_elf_to_process(const char *path, process_t **out_proc) {
    int fd = vfs_open(path);
    if (fd < 0) return -1;

    elf32_hdr_t ehdr;
    if (vfs_read_at(fd, (char*)&ehdr, sizeof(ehdr), 0) != sizeof(ehdr)) return -1;
    if (ehdr.e_magic != ELF_MAGIC) return -1;

    int phnum = ehdr.e_phnum;
    elf32_phdr_t *phdrs = kmalloc(phnum * sizeof(elf32_phdr_t));
    if (!phdrs) return -1;
    if (vfs_read_at(fd, (char*)phdrs, phnum * sizeof(elf32_phdr_t), ehdr.e_phoff) != phnum * sizeof(elf32_phdr_t)) {
        kfree(phdrs); return -1;
    }

    /* Create new page directory for this process */
    void *page_dir = create_page_directory();
    if (!page_dir) { kfree(phdrs); return -1; }

    /* Create process structure */
    process_t *p = create_process(NULL);
    if (!p) { kfree(phdrs); return -1; }

    /* Load each PT_LOAD segment */
    for (int i = 0; i < phnum; i++) {
        elf32_phdr_t *ph = &phdrs[i];
        if (ph->p_type != PT_LOAD) continue;

        uint32_t vstart = ph->p_vaddr;
        uint32_t vend = ph->p_vaddr + ph->p_memsz;
        uint32_t page_start = PAGE_ALIGN_DOWN(vstart);
        uint32_t page_end = PAGE_ALIGN_UP(vend);
        size_t alloc_pages = (page_end - page_start) / PAGE_SIZE;

        void *phys = pfa_alloc_pages(alloc_pages);
        if (!phys) { kfree(phdrs); return -1; }
        memset(phys, 0, alloc_pages * PAGE_SIZE);

        if (ph->p_filesz > 0) {
            if (vfs_read_at(fd, (char*)phys + (vstart - page_start), ph->p_filesz, ph->p_offset) != (int)ph->p_filesz) {
                kfree(phdrs); return -1;
            }
        }

        /* Map physical memory to virtual address in process page directory */
        int flags = 0x3; /* present + writable */
        if (ph->p_flags & 0x1) flags |= 0x4; /* executable -> user */
        map_segment_to_vaddr(page_dir, phys, page_start, page_end - page_start, flags);
    }

    /* Allocate user stack */
    #define STACK_PAGES 16
    void *stack_phys = pfa_alloc_pages(STACK_PAGES);
    if (!stack_phys) { kfree(phdrs); return -1; }
    memset(stack_phys, 0, STACK_PAGES * PAGE_SIZE);
    
    /* Map stack at high virtual address (e.g., 0xC0000000 - 64KB) */
    uint32_t stack_vaddr = 0xC0000000 - (STACK_PAGES * PAGE_SIZE);
    map_segment_to_vaddr(page_dir, stack_phys, stack_vaddr, STACK_PAGES * PAGE_SIZE, 0x3);

    /* Set up CPU state for first run */
    p->cpu.eip = ehdr.e_entry;
    p->cpu.esp = stack_vaddr + (STACK_PAGES * PAGE_SIZE) - 4; /* top of stack */
    p->cpu.eflags = 0x200; /* IF flag set */
    p->cpu.page_dir = page_dir;

    /* Push argc/argv onto stack (simple version) */
    uint32_t sp = p->cpu.esp;
    sp -= 4; *(uint32_t*)sp = 0; /* env = NULL */
    sp -= 4; *(uint32_t*)sp = 0; /* argv[0] = NULL */
    sp -= 4; *(uint32_t*)sp = 0; /* argc = 0 */
    p->cpu.esp = sp;

    *out_proc = p;
    kfree(phdrs);
    hal_console_write("ELF loaded successfully\n");
    return 0;
}

