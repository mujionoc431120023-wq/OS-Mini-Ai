#include "../include/framebuffer.h"
#include <stdint.h>

#define FB_BASE 0xA0000
static volatile uint32_t *fb = (uint32_t*)FB_BASE;
static uint32_t backbuf[640 * 480];

void fb_draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= 640 || y >= 480) return;
    backbuf[y * 640 + x] = color;
}

void fb_clear(uint32_t color) {
    for (int i = 0; i < 640 * 480; i++) backbuf[i] = color;
}

void fb_blit(void) {
    for (int i = 0; i < 640 * 480; i++) fb[i] = backbuf[i];
}

