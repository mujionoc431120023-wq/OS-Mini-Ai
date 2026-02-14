#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>

#define FB_WIDTH 640
#define FB_HEIGHT 480

void fb_draw_pixel(int x, int y, uint32_t color);
void fb_clear(uint32_t color);
void fb_blit(void);

#endif

