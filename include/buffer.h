#include <coreinit/cache.h>
#include <coreinit/screen.h>
#include <stdbool.h>

void set(void *tv, void *drc);
void enable();
void clear();
void flush(void *tv, uint32_t tvSize, void *drc, uint32_t drcSize);
void flip();