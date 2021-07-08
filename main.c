#include <vpad/input.h>
#include <whb/proc.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <coreinit/screen.h>
#include <coreinit/cache.h>

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
   OSScreenSetBufferEx(SCREEN_TV, tvBuffer);
   OSScreenSetBufferEx(SCREEN_DRC, drcBuffer);
   OSScreenEnableEx(SCREEN_TV, true);
   OSScreenEnableEx(SCREEN_DRC, true);

   while(WHBProcIsRunning()) {
        VPADRead(VPAD_CHAN_0, &status, 1, &error);
	    OSScreenClearBufferEx(SCREEN_TV, 0x00000000);
        OSScreenClearBufferEx(SCREEN_DRC, 0x00000000);
        OSScreenPutFontEx(SCREEN_TV, 0, 0, "Fix You Stick");
        OSScreenPutFontEx(SCREEN_TV, 0, 1, "By Xpl0itU");
        OSScreenPutFontEx(SCREEN_DRC, 0, 0, "Fix You Stick");
        OSScreenPutFontEx(SCREEN_DRC, 0, 1, "By Xpl0itU");
        OSScreenPutFontEx(SCREEN_TV, 0, 4, "Press the A button");
        OSScreenPutFontEx(SCREEN_DRC, 0, 4, "Press the A button");
        OSScreenPutFontEx(SCREEN_TV, 0, 16, "Please ensure the sticks");
        OSScreenPutFontEx(SCREEN_TV, 0, 17, "are in a neutral position");
        OSScreenPutFontEx(SCREEN_DRC, 0, 16, "Please ensure the sticks");
        OSScreenPutFontEx(SCREEN_DRC, 0, 17, "are in a neutral position");
        if (status.trigger & VPAD_BUTTON_A) {
            VPADSetStickOrigin(VPAD_CHAN_0);
            pressed = true;
        }
        if (pressed == true) {
            OSScreenPutFontEx(SCREEN_TV, 53, 17, "Done");
            OSScreenPutFontEx(SCREEN_DRC, 53, 17, "Done");
        }
        DCFlushRange(tvBuffer, tvBufferSize);
        DCFlushRange(drcBuffer, drcBufferSize);
        OSScreenFlipBuffersEx(SCREEN_TV);
        OSScreenFlipBuffersEx(SCREEN_DRC);
   }
   if (tvBuffer) free(tvBuffer);
   if (drcBuffer) free(drcBuffer);
   VPADShutdown();
   OSScreenShutdown();
   WHBProcShutdown();
   return 0;
}