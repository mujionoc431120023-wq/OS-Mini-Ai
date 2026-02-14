#ifndef FONT_H
#define FONT_H
#include <stdint.h>
void font_init(void);
void font_draw_char(int x, int y, char c, uint32_t color);
void font_draw_text(int x, int y, const char *s, uint32_t color);
int font_char_width(void);
int font_char_height(void);
#endif

