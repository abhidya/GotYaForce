/* gnt4_shim_seed.h — CORE_SEED for port_unit_generator (auto 1:1 chunk port).
 *
 * Forked from research/decomp/poc/wasm-port-poc/gnt4_shim.h (the PoC seed) so
 * the PoC's committed, oracle-verified units keep the header they were built
 * against. THIS copy is what every generated unit starts from, and it matches
 * the driver's SYSTEM_PROMPT (src/port_wasm_units.py) exactly:
 *   - undefined8 is an INTEGER (unsigned long long), never double
 *   - CONCAT44 is pure integer bit manipulation; the (double) cast and the
 *     ^ 0x80000000 in the PPC int->double idiom belong to the CALLER and are
 *     never folded into the macro (a double-returning CONCAT44 makes the xor
 *     illegal and the unit cannot compile)
 * The PoC seed instead used `typedef double undefined8` + a union bit-cast
 * CONCAT44 because its handful of call sites were all the fp trick; the auto
 * pipeline compiles arbitrary chunks, where CONCAT44 is used as an integer.
 *
 * Everything below the typedef/pseudo-op block is inherited from the PoC seed:
 *   - the DAT_/FLOAT_/DOUBLE_/PTR_ globals as macros that dereference the
 *     ORIGINAL GameCube addresses inside wasm linear memory (the "one memory
 *     arena at original addresses" design)
 *   - countLeadingZeros: PPC cntlzw semantics (cntlzw(0) == 32)
 *   - SDK functions (gnt4_*) as extern declarations -> wasm env imports
 *     (design stage 1: SDK is never ported).
 */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>  /* Ghidra emits `bool` for cr-bit results */

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

/* Ghidra pseudo-ops: pure integer bit manipulation. In the PPC int->double
 * idiom `(double)(CONCAT44(0x43300000, x) ^ 0x80000000) - 4503599627370496.0`
 * the xor and the cast are the caller's, not the macro's. */
#define CONCAT44(hi, lo) \
  (((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo))

/* PPC lfd-of-assembled-bits: reinterpret a u64 bit pattern as an IEEE754
 * double. The extraction transform (D5) rewrites Ghidra's reinterpretation
 * casts `(double)CONCAT44(...)` to this helper; a bare (double) cast on an
 * integer in unit.c is then always a genuine value conversion. */
static inline double __gnt4_bitcast_f64(unsigned long long __u) {
  union { unsigned long long u; double d; } __b;
  __b.u = __u;
  return __b.d;
}

/* PPC cntlzw: defined for 0 (returns 32), unlike __builtin_clz. */
static inline uint countLeadingZeros(int x) {
  return x == 0 ? 32u : (uint)__builtin_clz((unsigned int)x);
}

#define ABS(x) __builtin_fabs(x)

/* ---- arena globals: original GC addresses inside wasm linear memory ---- */
#define GC_F32(a)  (*(float *)(unsigned int)(a))
#define GC_F64(a)  (*(double *)(unsigned int)(a))
#define GC_U8(a)   (*(unsigned char *)(unsigned int)(a))
#define GC_S16(a)  (*(short *)(unsigned int)(a))
#define GC_PTR(a)  (*(char **)(unsigned int)(a))
#define GC_IPTR(a) (*(int *)(unsigned int)(a))

/* constants (sec12 .sdata2, DOL-initialized; values verified vs boot.dol) */
#define FLOAT_80436f68  GC_F32(0x80436f68)  /* 0.0  formula gate            */
#define FLOAT_80436f78  GC_F32(0x80436f78)  /* 1.0                          */
#define FLOAT_80436f7c  GC_F32(0x80436f7c)  /* 0.5                          */
#define FLOAT_80436f9c  GC_F32(0x80436f9c)  /* 2.0  attacker pair bonus     */
#define FLOAT_80437024  GC_F32(0x80437024)  /* 0.25 same-team divisor       */
#define FLOAT_80437028  GC_F32(0x80437028)  /* 40.0 guard divisor           */
#define DOUBLE_80436fb0 GC_F64(0x80436fb0)  /* 2^52   uint->double magic    */
#define DOUBLE_80436f88 GC_F64(0x80436f88)  /* 2^52+2^31 int->double magic  */

/* damage-table pointer slots (sec11 .data, DOL-initialized) */
#define PTR_DAT_804335e0 GC_PTR(0x804335e0)
#define PTR_PTR_804335e8 GC_PTR(0x804335e8)
#define PTR_PTR_804335f0 GC_PTR(0x804335f0)
#define PTR_DAT_804335f8 GC_PTR(0x804335f8)
#define PTR_PTR_80433600 GC_PTR(0x80433600)
#define PTR_PTR_80433608 GC_PTR(0x80433608)
#define PTR_PTR_80433610 GC_PTR(0x80433610)
#define PTR_DAT_80433618 GC_PTR(0x80433618)

/* runtime-struct pointers (DOL-initialized to fixed bss structs) */
#define PTR_DAT_80433930 GC_PTR(0x80433930)  /* -> 0x803c6ce0; [0x32] = challenge mode  */
#define PTR_DAT_80433934 GC_PTR(0x80433934)  /* -> 0x803c5420; [team*0x3c+0x114] = energy max */
#define PTR_DAT_80433950 GC_PTR(0x80433950)  /* -> 0x803c4e60; [team] = side-rank byte  */
#define PTR_DAT_80433954 GC_PTR(0x80433954)
#define DAT_8043625c     GC_IPTR(0x8043625c)

/* bss live-state arrays (harness-written per test case) */
#define DAT_803b069c GC_S16(0x803b069c)   /* s16 HP mirror, indexed by slot byte +0x3e4 */
#define DAT_803b068c GC_IPTR(0x803b068c)  /* int side energy, indexed by team byte +0x88 */

/* type-category remap (sec10 .data): (&PTR_DAT_802f2e28)[family] -> s16 row */
#define PTR_DAT_802f2e28 GC_IPTR(0x802f2e28)

/* combo-rank falloff table base (byte-addressed in source: &DAT + rank*4) */
#define DAT_802c7ca0 GC_U8(0x802c7ca0)

/* Unit B (FUN_80031634) data */
#define DAT_802cffc8 GC_U8(0x802cffc8)    /* char table, DOL-initialized, indexed *4 */
#define DAT_803b0720 GC_F32(0x803b0720)   /* bss vec3 out (x; +4 y; +8 z) */

/* ---- SDK seam (design stage 1): never ported, resolved as wasm env imports ---- */
extern void   gnt4_PSVECSubtract_bl(float *a, float *b, float *out);
extern undefined8 gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern undefined8 gnt4_PSQUATScale_bl(double s, float *v, float *out);
/* ---- SDK shims recovered from the corpus (2026-08-23) --------------------
 * The seed declared 6 gnt4_* functions; units referenced 66. The 60 with no
 * canonical declaration were invented per unit, so units disagreed and the
 * N=5 assembly link failed with collision_stub -- gnt4_PSVECMag_bl and
 * gnt4_PSQUATScale_bl among them.
 *
 * Every declaration below is DERIVED FROM THE CORPUS, not from recollection
 * of the GameCube SDK: the parameter types are those all referencing units
 * already agree on, and a void return is only used where NO call site in the
 * corpus consumes the result. Seven symbols whose return type cannot be
 * settled that way are deliberately absent and still contest:
 *   gnt4_PSMTXConcat_bl, gnt4_PSMTXCopy_bl, gnt4_PSMTXMultVec_bl,
 *   gnt4_PSMTXTrans_bl (results consumed, units split double/undefined8/void)
 *   gnt4_HSD_JObjReqAnimAll (declared void, result consumed)
 *   gnt4_HSD_JObjSetMtxDirtySub_bl, gnt4___assert_bl (parameter TYPES differ)
 * Those need a real SDK reference; guessing an f64/i64 return would silently
 * miscompile every caller and no compile-only green would catch it.
 */
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
extern void       gnt4_memcpy(void *dest, const void *src, size_t n);
extern void       gnt4_memset(void *dest, int c, size_t n);
extern double     gnt4_pow_bl(double base, double exp);
extern double     gnt4_sin_bl(double x);

/* Return type settled by CORPUS evidence, not by recollection: every call site
 * that consumes these assigns into a uVar (Ghidra's unsigned-integer naming),
 * never a dVar/fVar, so the decompiler captured r3 -- a GPR -- and the shim must
 * return an integer. Declaring `double` here would have given the wasm import an
 * f64 signature against an i64 caller. Left absent as genuinely unsettled:
 * gnt4_HSD_JObjSetMtxDirtySub_bl and gnt4___assert_bl, whose parameter TYPES
 * differ between units (a void pointer against an int pointer, a char pointer
 * against a float pointer), not merely their spelling. */
extern undefined8 gnt4_PSMTXConcat_bl(float *a, float *b, float *out);
extern undefined8 gnt4_PSMTXCopy_bl(float *src, float *dst);
extern undefined8 gnt4_PSMTXMultVec_bl(float *mtx, float *vec, float *out);
extern undefined8 gnt4_PSMTXTrans_bl(double x, double y, double z, float *out);
extern undefined8 gnt4_HSD_JObjReqAnimAll(int *jobj, double frame);

#endif /* GNT4_SHIM_H */
