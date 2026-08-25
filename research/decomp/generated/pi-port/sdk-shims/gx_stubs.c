#include "gnt4_sdk_shim.h"

static float gx_proj[7];               /* [0]=type (0=perspective,1=ortho), [1..6] coefficients */
static float gx_viewport[6];           /* left, top, width, height, nearz, farz */
static int   gx_scissor[4];            /* x, y, w, h */

void gnt4_GXSetProjection_bl(undefined4 *mtx, int param)
{
    const float *m = (const float *)mtx;
    gx_proj[0] = (float)param;
    if (param == 1) {
        /* orthographic */
        gx_proj[1] = m[0];
        gx_proj[2] = m[3];
        gx_proj[3] = m[5];
        gx_proj[4] = m[7];
        gx_proj[5] = m[10];
        gx_proj[6] = m[11];
    } else {
        /* perspective */
        gx_proj[1] = m[0];
        gx_proj[2] = m[2];
        gx_proj[3] = m[5];
        gx_proj[4] = m[6];
        gx_proj[5] = m[10];
        gx_proj[6] = m[11];
    }
}

void gnt4_GXGetProjectionv_bl(float *out)
{
    int i;
    for (i = 0; i < 7; i++)
        out[i] = gx_proj[i];
}

void gnt4_GXSetViewport_bl(double x, double y, double w, double h, double f1, double f2)
{
    gx_viewport[0] = (float)x;
    gx_viewport[1] = (float)y;
    gx_viewport[2] = (float)w;
    gx_viewport[3] = (float)h;
    gx_viewport[4] = (float)f1;
    gx_viewport[5] = (float)f2;
}

void gnt4_GXGetViewportv_bl(float *out)
{
    int i;
    for (i = 0; i < 6; i++)
        out[i] = gx_viewport[i];
}

void gnt4_GXSetScissor_bl(int x, int y, int w, int h)
{
    gx_scissor[0] = x;
    gx_scissor[1] = y;
    gx_scissor[2] = w;
    gx_scissor[3] = h;
}

void gnt4_GXProject_bl(double x, double y, double z, float *mtx1, float *mtx2, float *mtx3, float *ox, float *oy, float *oz)
{
    float fx = (float)x;
    float fy = (float)y;
    float fz = (float)z;
    const float *model = mtx1;
    const float *pm = mtx2;
    const float *vp = mtx3;
    float ex, ey, ez, xc, yc, zc, wc;

    ex = model[0]*fx + model[1]*fy + model[2]*fz  + model[3];
    ey = model[4]*fx + model[5]*fy + model[6]*fz  + model[7];
    ez = model[8]*fx + model[9]*fy + model[10]*fz + model[11];

    if (pm[0] == 0.0f) {
        /* perspective */
        xc = ex*pm[1] + ez*pm[2];
        yc = ey*pm[3] + ez*pm[4];
        zc = ez*pm[5] + pm[6];
        wc = 1.0f / -ez;
    } else {
        /* orthographic */
        xc = ex*pm[1] + pm[2];
        yc = ey*pm[3] + pm[4];
        zc = ez*pm[5] + pm[6];
        wc = 1.0f;
    }

    *ox = vp[0] + (vp[2]/2.0f) + (wc*xc*vp[2]/2.0f);
    *oy = vp[1] + (vp[3]/2.0f) - (wc*yc*vp[3]/2.0f);
    *oz = vp[5] + (wc*zc*(vp[5]-vp[4]));
}

void gnt4_GXInitLightColor_bl(int param1, undefined4 *colors)
{
    /* TODO stub: semantics deferred (corpus prototype does not carry the SDK's
       (GXLightObj*, GXColor) shape coherently). */
    (void)param1;
    (void)colors;
}

void gnt4_GXInitLightDistAttn_bl(double param1, double param2, int param3, int param4)
{
    /* TODO stub: semantics deferred. */
    (void)param1;
    (void)param2;
    (void)param3;
    (void)param4;
}

void gnt4_GXInitLightSpot_bl(double param1, int param2, int param3)
{
    /* TODO stub: semantics deferred. */
    (void)param1;
    (void)param2;
    (void)param3;
}
