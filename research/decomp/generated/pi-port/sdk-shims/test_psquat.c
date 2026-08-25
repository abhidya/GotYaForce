#include "gnt4_sdk_shim.h"
#include <stdio.h>
#include <math.h>

static const double TOL = 1e-5;

static int feq(double a, double b)
{
    return fabs(a - b) <= TOL;
}

int main(void)
{
    /* Test 1: DotProduct {1,2,3,4}.{5,6,7,8} == 70 */
    {
        float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
        float b[4] = {5.0f, 6.0f, 7.0f, 8.0f};
        double d = gnt4_PSQUATDotProduct_bl(a, b);
        if (!feq(d, 70.0)) { printf("FAIL: test1\n"); return 1; }
    }

    /* Test 2: unit quaternion dot itself == 1 */
    {
        float q[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        double d = gnt4_PSQUATDotProduct_bl(q, q);
        if (!feq(d, 1.0)) { printf("FAIL: test2\n"); return 1; }
    }

    /* Test 3: Scale {1,-2,3,-4} * 0.5 and return value */
    {
        float v[4] = {1.0f, -2.0f, 3.0f, -4.0f};
        float out[4];
        undefined8 ret = gnt4_PSQUATScale_bl(0.5, v, out);
        double expv[4] = {0.5, -1.0, 1.5, -2.0};
        for (int i = 0; i < 4; i++)
            if (!feq(out[i], expv[i])) { printf("FAIL: test3\n"); return 1; }
        if (ret != (undefined8)(unsigned int)(uintptr_t)v) { printf("FAIL: test3\n"); return 1; }
    }

    /* Test 4: normalize-style identity */
    {
        float q[4] = {3.0f, 0.0f, 4.0f, 0.0f};
        float r[4];
        double d = gnt4_PSQUATDotProduct_bl(q, q);
        double s = 1.0 / sqrt(d);
        gnt4_PSQUATScale_bl(s, q, r);
        double dr = gnt4_PSQUATDotProduct_bl(r, r);
        if (!feq(dr, 1.0)) { printf("FAIL: test4\n"); return 1; }
    }

    printf("PSQUAT_TESTS_PASS\n");
    return 0;
}
