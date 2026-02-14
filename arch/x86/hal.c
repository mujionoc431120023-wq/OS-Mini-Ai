#include "../include/hal.h"
#include <stdint.h>

/* Simple HAL - prints to serial port / debug output */
void hal_console_write(const char *s) {
    while (*s) {
        /* Output to VGA text memory for QEMU display */
        volatile uint16_t *vga = (uint16_t*)0xB8000;
        static int pos = 0;
        if (*s == '\n') {
            pos = (pos / 80 + 1) * 80;
        } else {
            vga[pos++] = (*s) | 0x0F00;
            if (pos >= 80*25) pos = 0;
        }
        s++;
    }
}

void hal_idle(void) {
    /* Simple halt - in real hardware would use hlt instruction */
    volatile int i = 0;
    while (i < 1000000) i++;
}

void hal_sleep(int ms) {
    volatile int i = 0;
    while (i < ms * 1000) i++;
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

