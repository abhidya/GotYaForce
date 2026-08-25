#include "gnt4_sdk_shim.h"
#include <stdio.h>
#include <math.h>

static int near_eq(float a, float b, float tol)
{
    float d = a - b;
    if (d < 0.0f) d = -d;
    return d <= tol;
}

int main(void)
{
    const float tol = 1e-4f;
    float m[16];

    /* Test 1: LookAt */
    {
        float camPos[3] = {0.0f, 0.0f, 10.0f};
        float camUp[3]  = {0.0f, 1.0f, 0.0f};
        float target[3] = {0.0f, 0.0f, 0.0f};

        gnt4_C_MTXLookAt_bl(m, camPos, camUp, target);

        if (!near_eq(m[0*4+0], 1.0f, tol) || !near_eq(m[0*4+1], 0.0f, tol) ||
            !near_eq(m[0*4+2], 0.0f, tol) || !near_eq(m[0*4+3], 0.0f, tol)) {
            printf("FAIL: LookAt row0\n");
            return 1;
        }
        if (!near_eq(m[1*4+0], 0.0f, tol) || !near_eq(m[1*4+1], 1.0f, tol) ||
            !near_eq(m[1*4+2], 0.0f, tol) || !near_eq(m[1*4+3], 0.0f, tol)) {
            printf("FAIL: LookAt row1\n");
            return 1;
        }
        if (!near_eq(m[2*4+0], 0.0f, tol) || !near_eq(m[2*4+1], 0.0f, tol) ||
            !near_eq(m[2*4+2], 1.0f, tol) || !near_eq(m[2*4+3], -10.0f, tol)) {
            printf("FAIL: LookAt row2\n");
            return 1;
        }
    }

    /* Test 2: LookAt orthonormality */
    {
        float camPos[3] = {3.0f, 4.0f, 5.0f};
        float camUp[3]  = {0.0f, 1.0f, 0.0f};
        float target[3] = {1.0f, 1.0f, 1.0f};

        gnt4_C_MTXLookAt_bl(m, camPos, camUp, target);

        for (int i = 0; i < 3; i++) {
            float r0 = m[i*4+0], r1 = m[i*4+1], r2 = m[i*4+2];
            float mag = sqrtf(r0*r0 + r1*r1 + r2*r2);
            if (!near_eq(mag, 1.0f, tol)) {
                printf("FAIL: LookAt orthonormality magnitude row%d\n", i);
                return 1;
            }
            for (int j = i + 1; j < 3; j++) {
                float dot = m[i*4+0]*m[j*4+0] + m[i*4+1]*m[j*4+1] + m[i*4+2]*m[j*4+2];
                if (!near_eq(dot, 0.0f, tol)) {
                    printf("FAIL: LookAt orthonormality dot row%d/row%d\n", i, j);
                    return 1;
                }
            }
        }
    }

    /* Test 3: Ortho */
    {
        gnt4_C_MTXOrtho_bl(1.0, -1.0, -1.0, 1.0, 0.0, 10.0, m);

        if (!near_eq(m[0*4+0], 1.0f, tol)) { printf("FAIL: Ortho m[0][0]\n"); return 1; }
        if (!near_eq(m[1*4+1], 1.0f, tol)) { printf("FAIL: Ortho m[1][1]\n"); return 1; }
        if (!near_eq(m[2*4+2], -0.1f, tol)) { printf("FAIL: Ortho m[2][2]\n"); return 1; }
        if (!near_eq(m[2*4+3], -1.0f, tol)) { printf("FAIL: Ortho m[2][3]\n"); return 1; }
        if (!near_eq(m[3*4+3], 1.0f, tol)) { printf("FAIL: Ortho m[3][3]\n"); return 1; }
        if (!near_eq(m[0*4+3], 0.0f, tol)) { printf("FAIL: Ortho m[0][3]\n"); return 1; }
        if (!near_eq(m[1*4+3], 0.0f, tol)) { printf("FAIL: Ortho m[1][3]\n"); return 1; }
    }

    /* Test 4: Perspective */
    {
        gnt4_C_MTXPerspective_bl(90.0, 1.0, 1.0, 100.0, m);

        if (!near_eq(m[0*4+0], 1.0f, tol)) { printf("FAIL: Perspective m[0][0]\n"); return 1; }
        if (!near_eq(m[1*4+1], 1.0f, tol)) { printf("FAIL: Perspective m[1][1]\n"); return 1; }
        if (!near_eq(m[3*4+2], -1.0f, tol)) { printf("FAIL: Perspective m[3][2]\n"); return 1; }
        if (!near_eq(m[3*4+3], 0.0f, tol)) { printf("FAIL: Perspective m[3][3]\n"); return 1; }
        if (!near_eq(m[2*4+2], -(1.0f/99.0f), tol)) { printf("FAIL: Perspective m[2][2]\n"); return 1; }
        if (!near_eq(m[2*4+3], -(100.0f/99.0f), tol)) { printf("FAIL: Perspective m[2][3]\n"); return 1; }
    }

    printf("C_MTX_TESTS_PASS\n");
    return 0;
}
