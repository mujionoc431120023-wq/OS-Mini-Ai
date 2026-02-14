#include "../include/memory.h"
#include <stdint.h>
#include <string.h>

#define MAX_FRAMES 16384

static uint8_t frame_bitmap[MAX_FRAMES / 8];
static uint32_t total_frames = MAX_FRAMES;

static inline void set_frame(uint32_t i) { frame_bitmap[i / 8] |= (1 << (i % 8)); }
static inline void clear_frame(uint32_t i) { frame_bitmap[i / 8] &= ~(1 << (i % 8)); }
static inline int test_frame(uint32_t i) { return (frame_bitmap[i / 8] >> (i % 8)) & 1; }

void pfa_init(void) { memset(frame_bitmap, 0, sizeof(frame_bitmap)); }

void *pfa_alloc_frame(void) {
    for (uint32_t i = 0; i < total_frames; i++) {
        if (!test_frame(i)) {
            set_frame(i);
            return (void*)(uintptr_t)(i * 4096);
        }
    }
    return NULL;
}

void pfa_free_frame(void *addr) {
    uint32_t frame = (uint32_t)((uintptr_t)addr / 4096);
    if (frame < total_frames) clear_frame(frame);
}

void *pfa_alloc_pages(uint32_t pages) {
    uint32_t run = 0;
    for (uint32_t i = 0; i < total_frames; i++) {
        if (!test_frame(i)) {
            run++;
            if (run == pages) {
                uint32_t start = i - pages + 1;
                for (uint32_t j = 0; j < pages; j++) set_frame(start + j);
                return (void*)(uintptr_t)(start * 4096);
            }
        } else {
            run = 0;
        }
    }
    return NULL;
}

