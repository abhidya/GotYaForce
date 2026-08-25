#include "gnt4_sdk_shim.h"
#include <stdio.h>
#include <math.h>

static int near_eq(float a, float b, float tol)
{
    return fabsf(a - b) <= tol;
}

int main(void)
{
    const float tol = 1e-4f;

    /* 1. Viewport roundtrip */
    gnt4_GXSetViewport_bl(0, 0, 640, 480, 0, 1);
    {
        float vp[6];
        gnt4_GXGetViewportv_bl(vp);
        if (!(near_eq(vp[0], 0.0f, tol) && near_eq(vp[1], 0.0f, tol) &&
              near_eq(vp[2], 640.0f, tol) && near_eq(vp[3], 480.0f, tol) &&
              near_eq(vp[4], 0.0f, tol) && near_eq(vp[5], 1.0f, tol))) {
            printf("FAIL: viewport roundtrip\n");
            return 1;
        }
    }

    /* 2. Scissor (no getter; just verify no crash) */
    gnt4_GXSetScissor_bl(1, 2, 3, 4);
    gnt4_GXSetScissor_bl(0, 0, 640, 480);

    /* 3. Projection roundtrip (orthographic) */
    {
        float m[16] = {0};
        m[0] = 0.1f;
        m[3] = -1.0f;
        m[5] = 0.2f;
        m[7] = -2.0f;
        m[10] = -0.5f;
        m[11] = -3.0f;
        m[15] = 1.0f;
        float p[7];
        gnt4_GXSetProjection_bl((undefined4 *)m, 1);
        gnt4_GXGetProjectionv_bl(p);
        if (!(near_eq(p[0], 1.0f, tol) && near_eq(p[1], 0.1f, tol) &&
              near_eq(p[2], -1.0f, tol) && near_eq(p[3], 0.2f, tol) &&
              near_eq(p[4], -2.0f, tol) && near_eq(p[5], -0.5f, tol) &&
              near_eq(p[6], -3.0f, tol))) {
            printf("FAIL: projection roundtrip\n");
            return 1;
        }
    }

    /* 4. GXProject orthographic */
    {
        float model[12] = {1,0,0,0, 0,1,0,0, 0,0,1,0};
        float pm[7]     = {1, 1,0, 1,0, 1,0};
        float vp[6]     = {0,0,100,100,0,1};
        float ox, oy, oz;
        gnt4_GXProject_bl(0.5, 0.5, -0.25, model, pm, vp, &ox, &oy, &oz);
        if (!(near_eq(ox, 75.0f, tol) && near_eq(oy, 25.0f, tol) &&
              near_eq(oz, 0.75f, tol))) {
            printf("FAIL: GXProject orthographic\n");
            return 1;
        }
    }

    /* 5. Light TODO stubs (arbitrary args), verify no crash */
    gnt4_GXInitLightColor_bl(0, (undefined4 *)0);
    gnt4_GXInitLightDistAttn_bl(0.0, 1.0, 0, 0);
    gnt4_GXInitLightSpot_bl(0.0, 0, 0);

    printf("GX_TESTS_PASS\n");
    return 0;
}
