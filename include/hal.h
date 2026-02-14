#ifndef HAL_H
#define HAL_H
#include <stdint.h>

void hal_console_write(const char *s);
void hal_idle(void);
void hal_sleep(int ms);
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

#endif

