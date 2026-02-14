#include "../include/font.h"
#include "../include/framebuffer.h"
#include "../fonts/font8x8.h"

static int cw = 8, ch = 8;

void font_init(void) { }

int font_char_width(void) { return cw; }
int font_char_height(void) { return ch; }

void font_draw_char(int x, int y, char c, uint32_t color) {
    if (c < 32 || c > 127) c = '?';
    const uint8_t *g = font8x8_basic[c - 32];
    for (int r = 0; r < ch; r++) {
        uint8_t bits = g[r];
        for (int b = 0; b < cw; b++) {
            if (bits & (1 << b)) fb_draw_pixel(x + b, y + r, color);
        }
    }
}

void font_draw_text(int x, int y, const char *s, uint32_t color) {
    int cx = x;
    while (*s) {
        font_draw_char(cx, y, *s++, color);
        cx += cw;
    }
}

