/* gnt4_sdk_shim.h — local prototype header for the pi-port SDK shim lane.
 *
 * Typedefs + EXACT gnt4_* prototypes copied verbatim from
 * research/decomp/generated/finish-game-port/gnt4_shim_seed.h.
 * Deliberately EXCLUDES the arena/address macros (GC_*, DAT_*, PTR_*):
 * shim implementations are portable C and must not touch GC addresses.
 */
#ifndef GNT4_SDK_SHIM_H
#define GNT4_SDK_SHIM_H

#include <stdbool.h>

/* Ghidra placeholder types: FIXED widths (driver SYSTEM_PROMPT contract). */
typedef unsigned char      undefined;
typedef unsigned char      undefined1;
typedef unsigned short     undefined2;
typedef unsigned int       undefined4;
typedef unsigned long long undefined8;  /* an INTEGER, never double */
typedef unsigned char      byte;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned long long ulonglong;
typedef long long          longlong;

/* ---- SDK seam prototypes (verbatim from gnt4_shim_seed.h) ---- */
extern void   gnt4_PSVECSubtract_bl(float *a, float *b, float *out);
extern undefined8 gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern undefined8 gnt4_PSQUATScale_bl(double s, float *v, float *out);

extern void       gnt4_C_MTXLookAt_bl(float *out, float *eye, float *center, float *up);
extern void       gnt4_C_MTXOrtho_bl(double f1, double f2, double f3, double f4, double f5, double f6, float *out);
extern void       gnt4_C_MTXPerspective_bl(double f1, double f2, double f3, double f4, float *out);
extern void       gnt4_GXGetProjectionv_bl(float *out);
extern void       gnt4_GXGetViewportv_bl(float *out);
extern void       gnt4_GXInitLightColor_bl(int param1, undefined4 *colors);
extern void       gnt4_GXInitLightDistAttn_bl(double param1, double param2, int param3, int param4);
extern void       gnt4_GXInitLightSpot_bl(double param1, int param2, int param3);
extern void       gnt4_GXProject_bl(double x, double y, double z, float *mtx1, float *mtx2, float *mtx3, float *ox, float *oy, float *oz);
extern void       gnt4_GXSetProjection_bl(undefined4 *mtx, int param);
extern void       gnt4_GXSetScissor_bl(int x, int y, int w, int h);
extern void       gnt4_GXSetViewport_bl(double x, double y, double w, double h, double f1, double f2);
extern void       gnt4_HSD_CObjGetEyePosition_bl();
extern int        gnt4_HSD_CObjGetFov_bl(int obj_ptr);
extern void       gnt4_HSD_CObjGetInterest_bl();
extern int        gnt4_HSD_CObjGetUpVector_bl();
extern void       gnt4_HSD_CObjGetViewingMtx_bl();
extern void       gnt4_HSD_CObjSetFar_bl(double param_1, int param_2);
extern void       gnt4_HSD_CObjSetNear_bl(double param_1, int param_2);
extern void       gnt4_HSD_CObjSetOrtho_bl(double param_1, double param_2, double param_3, double param_4, int param_5);
extern void       gnt4_HSD_CObjSetPerspective_bl(double param_1, double param_2, int param_3);
extern void       gnt4_HSD_CObjSetScissorx4_bl(int param_1, short param_2, short param_3, short param_4, short param_5);
extern void       gnt4_HSD_CObjSetViewportfx4_bl(double param_1, double param_2, double param_3, double param_4, int param_5);
extern undefined8 gnt4_HSD_DObjClearFlags_bl(int obj, int flags);
extern void       gnt4_HSD_DObjSetFlags_bl(int obj, int flags);
extern int        gnt4_HSD_FogLoadDesc_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, undefined4 *desc, undefined4 extra_r4, void *param_11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16);
extern void       gnt4_HSD_JObjAddAnimAll();
extern void       gnt4_HSD_JObjAddChild(undefined8, double, double, double, double, double, double, double, int, int, char *, undefined4, undefined4, undefined4, undefined4, undefined4);
extern void       gnt4_HSD_JObjAnimAll(undefined8, double, double, double, double, double, double, double, int *, undefined4, float *, undefined4, undefined4, undefined4, undefined4, undefined4);
extern undefined8 gnt4_HSD_JObjClearFlags(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int p9, uint p10, char *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16);
extern int        gnt4_HSD_JObjGetDObj(int param_1);
extern int *      gnt4_HSD_JObjLoadJoint(undefined8, double, double, double, double, double, double, double, int *, int, char *, undefined4, undefined4, undefined4, undefined4, undefined4);
extern undefined8 gnt4_HSD_JObjSetFlags(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int p9, uint p10, char *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16);
extern void       gnt4_HSD_JObjSetupMatrixSub_bl(undefined8, double, double, double, double, double, double, double, int *, uint, void *, undefined4, undefined4, undefined4, undefined4, undefined4);
extern int        gnt4_HSD_LObjLoadDesc_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *desc, undefined4 extra_r4, int param_11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16);
extern void       gnt4_HSD_LObjRemoveAll_bl(int obj_ptr);
extern undefined8 gnt4_HSD_MObjCompileTev_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *p9, undefined4 p10, char *p11, byte *p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16);
extern void       gnt4_HSD_MObjSetFlags_bl(int obj, uint flags);
extern void       gnt4_PSMTXIdentity_bl(float *param_1);
extern void       gnt4_PSMTXRotRad_bl(double angle, float *quat_out, int axis);
extern void       gnt4_PSMTXScale_bl(double sx, double sy, double sz, float *out);
extern void       gnt4_PSVECCrossProduct_bl(float *a, float *b, float *out);
extern double     gnt4_PSVECMag_bl(float *v);
extern void       gnt4_PSVECNormalize_bl(float *in, float *out);
extern double     gnt4_PSVECSquareDistance_bl(float *a, float *b);
extern double     gnt4_PSVECSquareMag_bl(float *v);
extern void       gnt4___OSCacheInit_bl(void);
extern void       gnt4___OSFPRInit_bl(void);
extern void       gnt4___OSPSInit_bl(void);
extern int        gnt4___cvt_fp2unsigned_bl(double d);
extern void       gnt4___init_hardware_bl(void);
extern undefined8 gnt4___init_user_bl(void);
extern double     gnt4_acos_bl(double x);
extern double     gnt4_atan(double x);
extern double     gnt4_atan2_bl(double y, double x);
extern void       gnt4_memcpy(void *dest, const void *src, unsigned long n);
extern void       gnt4_memset(void *dest, int c, unsigned long n);
extern double     gnt4_pow_bl(double base, double exp);
extern double     gnt4_sin_bl(double x);

extern undefined8 gnt4_PSMTXConcat_bl(float *a, float *b, float *out);
extern undefined8 gnt4_PSMTXCopy_bl(float *src, float *dst);
extern undefined8 gnt4_PSMTXMultVec_bl(float *mtx, float *vec, float *out);
extern undefined8 gnt4_PSMTXTrans_bl(double x, double y, double z, float *out);
extern undefined8 gnt4_HSD_JObjReqAnimAll(int *jobj, double frame);

#endif /* GNT4_SDK_SHIM_H */
