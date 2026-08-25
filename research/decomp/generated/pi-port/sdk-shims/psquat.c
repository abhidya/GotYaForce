#include "gnt4_sdk_shim.h"
#include <stdint.h>

double gnt4_PSQUATDotProduct_bl(float *a, float *b)
{
    float acc = a[0] * b[0];
    acc += a[1] * b[1];
    acc += a[2] * b[2];
    acc += a[3] * b[3];
    return (double)acc;
}

undefined8 gnt4_PSQUATScale_bl(double s, float *v, float *out)
{
    float fs = (float)s;
    for (int i = 0; i < 4; i++)
        out[i] = v[i] * fs;
    return (undefined8)(unsigned int)(uintptr_t)v;
}
