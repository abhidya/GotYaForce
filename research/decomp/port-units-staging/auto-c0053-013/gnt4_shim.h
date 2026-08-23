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
#include <math.h>

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

/* PPC cntlzw: defined for 0 (returns 32), unlike __builtin_clz. */
static inline uint countLeadingZeros(int x) {
  return x == 0 ? 32u : (uint)__builtin_clz((unsigned int)x);
}

#define ABS(x) __builtin_fabs(x)
#define SQRT(x) sqrt(x)

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
extern void   gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern void   gnt4_PSQUATScale_bl(double s, float *v, float *out);
extern void   gnt4_PSMTXMultVec_bl(float *m, float *v, float *out);
extern double gnt4_PSVECMag_bl(float *v);
extern double gnt4_atan(double x);

#endif /* GNT4_SHIM_H */

/* ---- AUTO-GENERATED (port_unit_generator) ---- */
/* Ghidra `code` for indirect dispatch: unprototyped so any-arg calls
 * compile. Staging units are never executed; address->wasm-table
 * dispatch mapping is a later pipeline stage. */
typedef void (code)();

/* unit-referenced globals + external callees; widths are prefix-derived defaults
 * (the compile-fix loop may refine them). */
#define DAT_80382450 GC_U8(0x80382450)
#define DAT_8038245e GC_U8(0x8038245e)
#define DAT_8038246c GC_U8(0x8038246c)
#define DOUBLE_8043ba80 GC_F64(0x8043ba80)
#define DOUBLE_8043ba88 GC_F64(0x8043ba88)
#define FLOAT_8043ba5c GC_F32(0x8043ba5c)
#define FLOAT_8043ba60 GC_F32(0x8043ba60)
#define FLOAT_8043ba74 GC_F32(0x8043ba74)
#define FLOAT_8043ba78 GC_F32(0x8043ba78)
#define FLOAT_8043ba90 GC_F32(0x8043ba90)
#define FLOAT_8043ba94 GC_F32(0x8043ba94)
#define FLOAT_8043ba98 GC_F32(0x8043ba98)
#define FLOAT_8043ba9c GC_F32(0x8043ba9c)
#define FLOAT_8043baa0 GC_F32(0x8043baa0)
#define FLOAT_8043baa4 GC_F32(0x8043baa4)

extern int zz_00076d0_();
extern int zz_00097b4_();
extern int zz_0046588_();
extern int zz_0048288_();
extern int zz_006de10_();
extern int zz_0085e00_();
extern int zz_0088e50_();
extern int zz_0089100_();
extern int zz_0089444_();
extern int zz_008aff0_();
extern int zz_00f036c_();
