#include "gnt4_sdk_shim.h"
#include <math.h>
#include <stdint.h>

void gnt4_PSMTXIdentity_bl(float *param_1)
{
    int r, c;
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 4; c++) {
            param_1[r*4+c] = (r == c) ? 1.0f : 0.0f;
        }
    }
}

undefined8 gnt4_PSMTXCopy_bl(float *src, float *dst)
{
    int i;
    for (i = 0; i < 12; i++) {
        dst[i] = src[i];
    }
    return (undefined8)(unsigned int)(uintptr_t)src;
}

undefined8 gnt4_PSMTXConcat_bl(float *a, float *b, float *out)
{
    float tmp[12];
    int r, c, k;
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 4; c++) {
            float s = 0.0f;
            for (k = 0; k < 3; k++) {
                s += a[r*4+k] * b[k*4+c];
            }
            if (c == 3) {
                s += a[r*4+3];
            }
            tmp[r*4+c] = s;
        }
    }
    for (r = 0; r < 12; r++) {
        out[r] = tmp[r];
    }
    return (undefined8)(unsigned int)(uintptr_t)a;
}

undefined8 gnt4_PSMTXMultVec_bl(float *mtx, float *vec, float *out)
{
    float v0 = vec[0], v1 = vec[1], v2 = vec[2];
    out[0] = mtx[0]*v0 + mtx[1]*v1 + mtx[2]*v2 + mtx[3];
    out[1] = mtx[4]*v0 + mtx[5]*v1 + mtx[6]*v2 + mtx[7];
    out[2] = mtx[8]*v0 + mtx[9]*v1 + mtx[10]*v2 + mtx[11];
    return (undefined8)(unsigned int)(uintptr_t)mtx;
}

undefined8 gnt4_PSMTXTrans_bl(double x, double y, double z, float *out)
{
    out[0] = 1.0f; out[1] = 0.0f; out[2] = 0.0f; out[3] = (float)x;
    out[4] = 0.0f; out[5] = 1.0f; out[6] = 0.0f; out[7] = (float)y;
    out[8] = 0.0f; out[9] = 0.0f; out[10] = 1.0f; out[11] = (float)z;
    return (undefined8)(unsigned int)(uintptr_t)out;
}

void gnt4_PSMTXScale_bl(double sx, double sy, double sz, float *out)
{
    int i;
    for (i = 0; i < 12; i++) {
        out[i] = 0.0f;
    }
    out[0] = (float)sx;
    out[5] = (float)sy;
    out[10] = (float)sz;
}

void gnt4_PSMTXRotRad_bl(double angle, float *quat_out, int axis)
{
    float s = sinf((float)angle);
    float c = cosf((float)angle);
    switch (axis) {
        case 'x':
        case 'X':
            quat_out[0] = 1.0f; quat_out[1] = 0.0f; quat_out[2] = 0.0f; quat_out[3] = 0.0f;
            quat_out[4] = 0.0f; quat_out[5] = c;     quat_out[6] = -s;    quat_out[7] = 0.0f;
            quat_out[8] = 0.0f; quat_out[9] = s;     quat_out[10] = c;    quat_out[11] = 0.0f;
            break;
        case 'y':
        case 'Y':
            quat_out[0] = c;    quat_out[1] = 0.0f; quat_out[2] = s;     quat_out[3] = 0.0f;
            quat_out[4] = 0.0f; quat_out[5] = 1.0f; quat_out[6] = 0.0f;  quat_out[7] = 0.0f;
            quat_out[8] = -s;   quat_out[9] = 0.0f; quat_out[10] = c;    quat_out[11] = 0.0f;
            break;
        case 'z':
        case 'Z':
            quat_out[0] = c;    quat_out[1] = -s;    quat_out[2] = 0.0f; quat_out[3] = 0.0f;
            quat_out[4] = s;    quat_out[5] = c;     quat_out[6] = 0.0f; quat_out[7] = 0.0f;
            quat_out[8] = 0.0f; quat_out[9] = 0.0f;  quat_out[10] = 1.0f; quat_out[11] = 0.0f;
            break;
        default:
            break;
    }
}
