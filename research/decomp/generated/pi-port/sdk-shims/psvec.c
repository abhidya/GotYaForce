#include "gnt4_sdk_shim.h"
#include <math.h>
#include <stdint.h>

void gnt4_PSVECSubtract_bl(float *a, float *b, float *out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

undefined8 gnt4_PSVECAdd_bl(float *a, float *b, float *out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    return (undefined8)(unsigned int)(uintptr_t)a;
}

void gnt4_PSVECCrossProduct_bl(float *a, float *b, float *out)
{
    float x = a[1] * b[2] - a[2] * b[1];
    float y = a[2] * b[0] - a[0] * b[2];
    float z = a[0] * b[1] - a[1] * b[0];
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

double gnt4_PSVECMag_bl(float *v)
{
    float mag2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    return (double)sqrtf(mag2);
}

void gnt4_PSVECNormalize_bl(float *in, float *out)
{
    float mag2 = in[0] * in[0] + in[1] * in[1] + in[2] * in[2];
    float inv = 1.0f / sqrtf(mag2);
    out[0] = in[0] * inv;
    out[1] = in[1] * inv;
    out[2] = in[2] * inv;
}

double gnt4_PSVECSquareDistance_bl(float *a, float *b)
{
    float dx = a[0] - b[0];
    float dy = a[1] - b[1];
    float dz = a[2] - b[2];
    return (double)(dx * dx + dy * dy + dz * dz);
}

double gnt4_PSVECSquareMag_bl(float *v)
{
    return (double)(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
