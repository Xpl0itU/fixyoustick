#include <vpad/input.h>
#include <whb/proc.h>

int main(int argc, char **argv)
{
   WHBProcInit();
   VPADInit();

   VPADSetStickOrigin(VPAD_CHAN_0);

   VPADShutdown();
   WHBProcShutdown();
   return 0;
}