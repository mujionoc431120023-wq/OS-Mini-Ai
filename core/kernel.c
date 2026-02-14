#include "../include/hal.h"
#include "../include/process.h"

extern void init_scheduler(void);
extern void paging_init_identity(void);
extern void pfa_init(void);

void init_drivers(void) {
    hal_console_write("Drivers init\n");
}

void init_filesystems(void) {
    hal_console_write("Filesystems init\n");
}

void init_gui(void) {
    hal_console_write("GUI init\n");
}

void kernel_main(void) {
    pfa_init();
    hal_console_write("PFA init done\n");
    paging_init_identity();
    hal_console_write("Paging enabled\n");
    init_scheduler();
    hal_console_write("Scheduler init\n");
    hal_console_write("Kernel: booting...\n");
    init_drivers();
    init_filesystems();
    init_gui();
    hal_console_write("Kernel: GUI loop ready\n");
    
    while (1) hal_idle();
}

