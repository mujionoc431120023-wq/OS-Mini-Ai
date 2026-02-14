#ifndef PROCESS_H
#define PROCESS_H
#include <stdint.h>

typedef struct cpu_state {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t eip;
    uint32_t eflags;
    uint32_t user_esp;
    void *page_dir;
} cpu_state_t;

typedef struct process {
    int pid;
    void (*entry)(void);
    struct process *next;
    cpu_state_t cpu;
    int state;
} process_t;

void init_scheduler(void);
process_t* create_process(void (*entry)(void));
void enqueue_process(process_t *p);
process_t* dequeue_process(void);
extern process_t *current;
#endif

