#include "gnt4_sdk_shim.h"
#include <stdio.h>
#include <math.h>

static int near_eq(float a, float b) {
    float d = a - b;
    if (d < 0.0f) d = -d;
    return d <= 1e-5f;
}

int main(void) {
    float m[12], src[12], dst[12], out[12], A[12], I[12];
    int i, ok;

    /* 1. Identity */
    gnt4_PSMTXIdentity_bl(m);
    ok = 1;
    for (i = 0; i < 12; i++) {
        float e = ((i % 4) == (i / 4)) ? 1.0f : 0.0f;
        if (!near_eq(m[i], e)) { ok = 0; break; }
    }
    if (!ok) { printf("FAIL: identity\n"); return 1; }

    /* 2. Copy */
    for (i = 0; i < 12; i++) src[i] = (float)(i + 1);
    undefined8 rc = gnt4_PSMTXCopy_bl(src, dst);
    ok = 1;
    for (i = 0; i < 12; i++) { if (!near_eq(dst[i], src[i])) { ok = 0; break; } }
    if (!ok || rc != (undefined8)(unsigned int)(uintptr_t)src) { printf("FAIL: copy\n"); return 1; }

    /* 3. Concat with identity */
    for (i = 0; i < 12; i++) A[i] = (float)(i + 1);
    gnt4_PSMTXIdentity_bl(I);
    gnt4_PSMTXConcat_bl(I, A, out);
    ok = 1;
    for (i = 0; i < 12; i++) { if (!near_eq(out[i], A[i])) { ok = 0; break; } }
    if (!ok) { printf("FAIL: concat I*A\n"); return 1; }
    gnt4_PSMTXConcat_bl(A, I, out);
    ok = 1;
    for (i = 0; i < 12; i++) { if (!near_eq(out[i], A[i])) { ok = 0; break; } }
    if (!ok) { printf("FAIL: concat A*I\n"); return 1; }

    /* 4. Concat translation composition */
    gnt4_PSMTXTrans_bl(1, 2, 3, I);
    gnt4_PSMTXTrans_bl(10, 20, 30, A);
    gnt4_PSMTXConcat_bl(I, A, out);
    gnt4_PSMTXTrans_bl(11, 22, 33, m);
    ok = 1;
    for (i = 0; i < 12; i++) { if (!near_eq(out[i], m[i])) { ok = 0; break; } }
    if (!ok) { printf("FAIL: concat translation\n"); return 1; }

    /* 5. Concat aliasing */
    gnt4_PSMTXTrans_bl(1, 2, 3, A);
    gnt4_PSMTXTrans_bl(10, 20, 30, dst);
    gnt4_PSMTXConcat_bl(A, dst, A);
    gnt4_PSMTXTrans_bl(11, 22, 33, m);
    ok = 1;
    for (i = 0; i < 12; i++) { if (!near_eq(A[i], m[i])) { ok = 0; break; } }
    if (!ok) { printf("FAIL: concat aliasing\n"); return 1; }

    /* 6. MultVec */
    gnt4_PSMTXTrans_bl(1, 2, 3, m);
    float v[3] = {5, 6, 7};
    float r3[3];
    gnt4_PSMTXMultVec_bl(m, v, r3);
    if (!near_eq(r3[0], 6) || !near_eq(r3[1], 8) || !near_eq(r3[2], 10)) { printf("FAIL: multvec trans\n"); return 1; }
    gnt4_PSMTXRotRad_bl(3.14159265358979323846 / 2.0, m, 'z');
    float v2[3] = {1, 0, 0};
    gnt4_PSMTXMultVec_bl(m, v2, r3);
    if (!near_eq(r3[0], 0) || !near_eq(r3[1], 1) || !near_eq(r3[2], 0)) { printf("FAIL: multvec rotz\n"); return 1; }

    /* 7. RotRad x by pi */
    gnt4_PSMTXRotRad_bl(3.14159265358979323846, m, 'x');
    float v3[3] = {0, 1, 0};
    gnt4_PSMTXMultVec_bl(m, v3, r3);
    if (!near_eq(r3[0], 0) || !near_eq(r3[1], -1) || !near_eq(r3[2], 0)) { printf("FAIL: rotx pi\n"); return 1; }

    /* 8. Scale */
    gnt4_PSMTXScale_bl(2, 3, 4, m);
    float v4[3] = {1, 1, 1};
    gnt4_PSMTXMultVec_bl(m, v4, r3);
    if (!near_eq(r3[0], 2) || !near_eq(r3[1], 3) || !near_eq(r3[2], 4)) { printf("FAIL: scale\n"); return 1; }

    printf("PSMTX_TESTS_PASS\n");
    return 0;
}
