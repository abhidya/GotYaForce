#include "gnt4_sdk_shim.h"
#include <math.h>

void gnt4_C_MTXLookAt_bl(float *out, float *eye, float *center, float *up)
{
    /* out = m (3x4 view matrix), eye = camPos, center = camUp, up = target */
    float camPos[3]  = { eye[0],  eye[1],  eye[2]  };
    float camUp[3]   = { center[0], center[1], center[2] };
    float target[3]  = { up[0],   up[1],   up[2]   };

    float look[3];
    float right[3];
    float u[3];
    float len;

    /* look = normalize(camPos - target) */
    look[0] = camPos[0] - target[0];
    look[1] = camPos[1] - target[1];
    look[2] = camPos[2] - target[2];
    len = sqrtf(look[0]*look[0] + look[1]*look[1] + look[2]*look[2]);
    if (len != 0.0f) {
        look[0] /= len; look[1] /= len; look[2] /= len;
    }

    /* right = normalize(cross(camUp, look)) */
    right[0] = camUp[1]*look[2] - camUp[2]*look[1];
    right[1] = camUp[2]*look[0] - camUp[0]*look[2];
    right[2] = camUp[0]*look[1] - camUp[1]*look[0];
    len = sqrtf(right[0]*right[0] + right[1]*right[1] + right[2]*right[2]);
    if (len != 0.0f) {
        right[0] /= len; right[1] /= len; right[2] /= len;
    }

    /* u = cross(look, right) */
    u[0] = look[1]*right[2] - look[2]*right[1];
    u[1] = look[2]*right[0] - look[0]*right[2];
    u[2] = look[0]*right[1] - look[1]*right[0];

    out[0*4+0] = right[0]; out[0*4+1] = right[1]; out[0*4+2] = right[2];
    out[0*4+3] = -(camPos[0]*right[0] + camPos[1]*right[1] + camPos[2]*right[2]);

    out[1*4+0] = u[0]; out[1*4+1] = u[1]; out[1*4+2] = u[2];
    out[1*4+3] = -(camPos[0]*u[0] + camPos[1]*u[1] + camPos[2]*u[2]);

    out[2*4+0] = look[0]; out[2*4+1] = look[1]; out[2*4+2] = look[2];
    out[2*4+3] = -(camPos[0]*look[0] + camPos[1]*look[1] + camPos[2]*look[2]);
}

void gnt4_C_MTXOrtho_bl(double f1, double f2, double f3, double f4, double f5, double f6, float *out)
{
    float t = (float)f1;
    float b = (float)f2;
    float l = (float)f3;
    float r = (float)f4;
    float n = (float)f5;
    float f = (float)f6;
    float tmp;

    for (int i = 0; i < 16; i++) out[i] = 0.0f;

    tmp = 1.0f / (r - l);
    out[0*4+0] = 2.0f * tmp;
    out[0*4+3] = -(r + l) * tmp;

    tmp = 1.0f / (t - b);
    out[1*4+1] = 2.0f * tmp;
    out[1*4+3] = -(t + b) * tmp;

    tmp = 1.0f / (f - n);
    out[2*4+2] = -1.0f * tmp;
    out[2*4+3] = -f * tmp;

    out[3*4+3] = 1.0f;
}

void gnt4_C_MTXPerspective_bl(double f1, double f2, double f3, double f4, float *out)
{
    float fovY   = (float)f1;
    float aspect = (float)f2;
    float n      = (float)f3;
    float f      = (float)f4;
    float angle;
    float cot;
    float tmp;

    for (int i = 0; i < 16; i++) out[i] = 0.0f;

    angle = fovY * 0.5f;
    angle = angle * (3.14159265358979f / 180.0f);
    cot = 1.0f / tanf(angle);

    out[0*4+0] = cot / aspect;
    out[1*4+1] = cot;

    tmp = 1.0f / (f - n);
    out[2*4+2] = -n * tmp;
    out[2*4+3] = -(f * n) * tmp;

    out[3*4+2] = -1.0f;
}
