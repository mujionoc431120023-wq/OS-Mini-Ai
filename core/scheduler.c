#include "../include/process.h"
#include "../include/hal.h"

static process_t *ready = 0;
process_t *current = 0;

void init_scheduler(void) { ready = 0; current = 0; }

void enqueue_process(process_t *p) {
    if (!ready) { ready = p; p->next = p; }
    else {
        p->next = ready->next;
        ready->next = p;
    }
}

process_t* dequeue_process(void) {
    if (!ready) return 0;
    process_t *p = ready->next;
    if (p == ready) ready = 0;
    else ready->next = p->next;
    p->next = 0;
    return p;
}

void schedule(void) {
    if (current) enqueue_process(current);
    current = dequeue_process();
    if (current) {
        /* Switch to process page directory */
        if (current->cpu.page_dir) {
            asm volatile ("mov %0, %%cr3" :: "r"(current->cpu.page_dir));
        }
        /* Jump to user entry using iret */
        /* For now, just call entry directly (non-preemptive) */
        current->entry();
    } else {
        hal_idle();
    }
}

