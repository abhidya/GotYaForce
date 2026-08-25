#include "gnt4_sdk_shim.h"
#include <math.h>
#include <string.h>

void gnt4_memcpy(void *dest, const void *src, size_t n)
{
    memcpy(dest, src, n);
}

void gnt4_memset(void *dest, int c, size_t n)
{
    memset(dest, c, n);
}

double gnt4_acos_bl(double x)
{
    return acos(x);
}

double gnt4_atan(double x)
{
    return atan(x);
}

double gnt4_atan2_bl(double y, double x)
{
    return atan2(y, x);
}

double gnt4_pow_bl(double base, double exp)
{
    return pow(base, exp);
}

double gnt4_sin_bl(double x)
{
    return sin(x);
}
