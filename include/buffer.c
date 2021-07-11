#include "buffer.h"

void set(void *tv, void *drc) {
    OSScreenSetBufferEx(SCREEN_TV, tv);
    OSScreenSetBufferEx(SCREEN_DRC, drc);
}

void enable() {
    OSScreenEnableEx(SCREEN_TV, true);
    OSScreenEnableEx(SCREEN_DRC, true);
}

void clear() {
    OSScreenClearBufferEx(SCREEN_TV, 0x00000000);
    OSScreenClearBufferEx(SCREEN_DRC, 0x00000000);
}

void flush(void *tv, uint32_t tvSize, void *drc, uint32_t drcSize) {
    DCFlushRange(tv, tvSize);
    DCFlushRange(drc, drcSize);
}

void flip() {
    OSScreenFlipBuffersEx(SCREEN_TV);
    OSScreenFlipBuffersEx(SCREEN_DRC);
}