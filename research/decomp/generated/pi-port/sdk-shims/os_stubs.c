#include "gnt4_sdk_shim.h"

void gnt4___OSCacheInit_bl(void)
{
    /* no-op: no cache to initialize in a portable recreation */
}

void gnt4___OSFPRInit_bl(void)
{
    /* no-op: no FPR bank to initialize in a portable recreation */
}

void gnt4___OSPSInit_bl(void)
{
    /* no-op: paired-single mode not applicable in a portable recreation */
}

void gnt4___init_hardware_bl(void)
{
    /* no-op: no hardware to initialize in a portable recreation */
}

undefined8 gnt4___init_user_bl(void)
{
    /* no-op: nothing to set up for user init; return 0 */
    return 0;
}

int gnt4___cvt_fp2unsigned_bl(double d)
{
    /* PPC double -> unsigned 32-bit conversion with saturation.
       - d != d (NaN)         -> 0
       - d <= 0.0             -> 0
       - d >= 4294967295.0    -> 0xFFFFFFFF
       - else truncate toward zero: (unsigned int)d
       Returned through the declared `int` return type (same 32 bits). */
    if (d != d)
        return 0;
    if (d <= 0.0)
        return 0;
    if (d >= 4294967295.0)
        return (int)0xFFFFFFFFu;
    return (int)(unsigned int)d;
}
