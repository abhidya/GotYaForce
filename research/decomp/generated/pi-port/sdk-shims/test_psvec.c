#include "gnt4_sdk_shim.h"
#include <stdio.h>
#include <math.h>

static int feq(float a, float b) { return fabsf(a - b) <= 1e-5f; }
static int deq(double a, double b) { return fabs(a - b) <= 1e-5; }
static int veq(float *a, float *b) { return feq(a[0], b[0]) && feq(a[1], b[1]) && feq(a[2], b[2]); }

int main(void)
{
    /* 1. Add */
    {
        float a[3] = {1, 2, 3}, b[3] = {4, 5, 6}, out[3];
        undefined8 r = gnt4_PSVECAdd_bl(a, b, out);
        float exp[3] = {5, 7, 9};
        if (!veq(out, exp)) { printf("FAIL: Add\n"); return 1; }
        if (r != (undefined8)(unsigned int)(uintptr_t)a) { printf("FAIL: Add return value\n"); return 1; }
    }

    /* 2. Subtract */
    {
        float a[3] = {5, 7, 9}, b[3] = {4, 5, 6}, out[3];
        gnt4_PSVECSubtract_bl(a, b, out);
        float exp[3] = {1, 2, 3};
        if (!veq(out, exp)) { printf("FAIL: Subtract\n"); return 1; }
    }

    /* 3. Cross */
    {
        float a[3] = {1, 0, 0}, b[3] = {0, 1, 0}, out[3];
        gnt4_PSVECCrossProduct_bl(a, b, out);
        float exp[3] = {0, 0, 1};
        if (!veq(out, exp)) { printf("FAIL: Cross\n"); return 1; }

        float v[3] = {1, 0, 0}, w[3] = {0, 1, 0};
        gnt4_PSVECCrossProduct_bl(v, w, v);
        if (!veq(v, exp)) { printf("FAIL: Cross aliasing\n"); return 1; }
    }

    /* 4. Mag */
    {
        float v[3] = {3, 4, 0};
        double m = gnt4_PSVECMag_bl(v);
        if (!deq(m, 5.0)) { printf("FAIL: Mag\n"); return 1; }
    }

    /* 5. SquareMag */
    {
        float v[3] = {1, 2, 2};
        double m = gnt4_PSVECSquareMag_bl(v);
        if (!deq(m, 9.0)) { printf("FAIL: SquareMag\n"); return 1; }
    }

    /* 6. SquareDistance */
    {
        float a[3] = {1, 1, 1}, b[3] = {2, 3, 3};
        double d = gnt4_PSVECSquareDistance_bl(a, b);
        if (!deq(d, 9.0)) { printf("FAIL: SquareDistance\n"); return 1; }
    }

    /* 7. Normalize */
    {
        float in[3] = {0, 3, 4}, out[3];
        gnt4_PSVECNormalize_bl(in, out);
        float exp[3] = {0, 0.6f, 0.8f};
        if (!veq(out, exp)) { printf("FAIL: Normalize\n"); return 1; }
        double m = gnt4_PSVECMag_bl(out);
        if (!deq(m, 1.0)) { printf("FAIL: Normalize mag\n"); return 1; }
    }

    printf("PSVEC_TESTS_PASS\n");
    return 0;
}
