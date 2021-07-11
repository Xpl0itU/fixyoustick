#include <vpad/input.h>
#include <whb/proc.h>
#include <stdint.h>
#include <malloc.h>
#include "include/draw.h"
#include "include/buffer.h"

int main(int argc, char **argv)
{
   WHBProcInit();
   OSScreenInit();
   VPADInit();
   VPADStatus status;
   VPADReadError error;
   bool pressed = false;
   size_t tvBufferSize = OSScreenGetBufferSizeEx(SCREEN_TV);
   size_t drcBufferSize = OSScreenGetBufferSizeEx(SCREEN_DRC);
   void* tvBuffer = memalign(0x100, tvBufferSize);
   void* drcBuffer = memalign(0x100, drcBufferSize);
   set(tvBuffer, drcBuffer);
   enable();

   while(WHBProcIsRunning()) {
        VPADRead(VPAD_CHAN_0, &status, 1, &error);
        clear();
        draw(0, 0, "Fix You Stick");
        draw(0, 1, "By Xpl0itU");
        draw(0, 4, "Press the A button");
        draw(0, 16, "Please ensure the sticks");
        draw(0, 17, "are in a neutral position");
        if (status.trigger & VPAD_BUTTON_A) {
            VPADSetStickOrigin(VPAD_CHAN_0);
            pressed = true;
        }
        if (pressed == true) {
            draw(53, 17, "Done");
        }
        flush(tvBuffer, tvBufferSize, drcBuffer, drcBufferSize);
        flip();
   }
   if (tvBuffer) free(tvBuffer);
   if (drcBuffer) free(drcBuffer);
   VPADShutdown();
   OSScreenShutdown();
   WHBProcShutdown();
   return 0;
}