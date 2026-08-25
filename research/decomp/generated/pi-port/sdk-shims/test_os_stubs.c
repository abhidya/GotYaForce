#include "gnt4_sdk_shim.h"
#include <stdio.h>

int main(void)
{
    /* 1. Call all four void no-ops and gnt4___init_user_bl */
    gnt4___OSCacheInit_bl();
    gnt4___OSFPRInit_bl();
    gnt4___OSPSInit_bl();
    gnt4___init_hardware_bl();

    if (gnt4___init_user_bl() != 0) {
        printf("FAIL: init_user returns 0\n");
        return 1;
    }

    /* 2. cvt_fp2unsigned */
    if ((unsigned int)gnt4___cvt_fp2unsigned_bl(0.0) != 0u) {
        printf("FAIL: cvt_fp2unsigned 0.0 -> 0\n");
        return 1;
    }

    if ((unsigned int)gnt4___cvt_fp2unsigned_bl(1.9) != 1u) {
        printf("FAIL: cvt_fp2unsigned 1.9 -> 1\n");
        return 1;
    }

    if ((unsigned int)gnt4___cvt_fp2unsigned_bl(4294967294.5) != 4294967294u) {
        printf("FAIL: cvt_fp2unsigned 4294967294.5 -> 4294967294\n");
        return 1;
    }

    if ((unsigned int)gnt4___cvt_fp2unsigned_bl(-5.0) != 0u) {
        printf("FAIL: cvt_fp2unsigned -5.0 -> 0\n");
        return 1;
    }

    if ((unsigned int)gnt4___cvt_fp2unsigned_bl(5e9) != 0xFFFFFFFFu) {
        printf("FAIL: cvt_fp2unsigned 5e9 -> 0xFFFFFFFF\n");
        return 1;
    }

    volatile double v = 0.0 / 0.0; /* NaN */
    if ((unsigned int)gnt4___cvt_fp2unsigned_bl(v) != 0u) {
        printf("FAIL: cvt_fp2unsigned NaN -> 0\n");
        return 1;
    }

    printf("OS_STUBS_TESTS_PASS\n");
    return 0;
}
