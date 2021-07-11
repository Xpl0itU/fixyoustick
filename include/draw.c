#include "draw.h"

void draw(int x, int y, char *text) {
    OSScreenPutFontEx(SCREEN_TV, x, y, text);
    OSScreenPutFontEx(SCREEN_DRC, x, y, text);
}