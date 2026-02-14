#include "../include/process.h"
#include <stdlib.h>
static int next_pid = 1;

process_t* create_process(void (*entry)(void)) {
    process_t *p = (process_t*)malloc(sizeof(process_t));
    if (!p) return 0;
    p->pid = next_pid++;
    p->entry = entry;
    p->next = 0;
    p->state = 0;
    p->cpu.page_dir = 0;
    return p;
}

