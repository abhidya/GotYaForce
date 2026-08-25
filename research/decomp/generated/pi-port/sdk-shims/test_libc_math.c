#include "gnt4_sdk_shim.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    const double PI = 3.14159265358979323846;
    const double TOL = 1e-9;

    /* 1. memcpy: copy 8 bytes {1..8} into a zeroed 8-byte buffer, verify bytes. */
    {
        unsigned char src[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        unsigned char dst[8];
        int i;
        gnt4_memset(dst, 0, sizeof(dst));
        gnt4_memcpy(dst, src, sizeof(src));
        for (i = 0; i < 8; i++) {
            if (dst[i] != src[i]) {
                printf("FAIL: memcpy\n");
                return 1;
            }
        }
    }

    /* 2. memset: set 8-byte buffer to 0x5A, verify. */
    {
        unsigned char buf[8];
        int i;
        gnt4_memset(buf, 0x5A, sizeof(buf));
        for (i = 0; i < 8; i++) {
            if (buf[i] != 0x5A) {
                printf("FAIL: memset\n");
                return 1;
            }
        }
    }

    /* 3. acos(1.0)==0, acos(0.0)==pi/2 */
    {
        if (fabs(gnt4_acos_bl(1.0) - 0.0) > TOL) {
            printf("FAIL: acos\n");
            return 1;
        }
        if (fabs(gnt4_acos_bl(0.0) - PI / 2.0) > TOL) {
            printf("FAIL: acos\n");
            return 1;
        }
    }

    /* 4. atan(1.0)==pi/4 */
    {
        if (fabs(gnt4_atan(1.0) - PI / 4.0) > TOL) {
            printf("FAIL: atan\n");
            return 1;
        }
    }

    /* 5. atan2(1.0,1.0)==pi/4; atan2(-1.0,-1.0)==-3*pi/4 */
    {
        if (fabs(gnt4_atan2_bl(1.0, 1.0) - PI / 4.0) > TOL) {
            printf("FAIL: atan2\n");
            return 1;
        }
        if (fabs(gnt4_atan2_bl(-1.0, -1.0) - (-3.0 * PI / 4.0)) > TOL) {
            printf("FAIL: atan2\n");
            return 1;
        }
    }

    /* 6. pow(2.0,10.0)==1024 */
    {
        if (fabs(gnt4_pow_bl(2.0, 10.0) - 1024.0) > TOL) {
            printf("FAIL: pow\n");
            return 1;
        }
    }

    /* 7. sin(pi/2)==1 (tolerance 1e-9); sin(0)==0 */
    {
        if (fabs(gnt4_sin_bl(PI / 2.0) - 1.0) > TOL) {
            printf("FAIL: sin\n");
            return 1;
        }
        if (fabs(gnt4_sin_bl(0.0) - 0.0) > TOL) {
            printf("FAIL: sin\n");
            return 1;
        }
    }

    printf("LIBC_MATH_TESTS_PASS\n");
    return 0;
}
