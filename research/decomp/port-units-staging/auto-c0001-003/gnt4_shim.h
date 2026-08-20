/* gnt4_shim.h — POC stage-2 "header + arena" scaffold (HANDOFF-2026-08-09 §4).
 *
 * Deterministically generated support header. The ported .c bodies are verbatim
 * sed-extractions from research/decomp/ghidra-export/ (see build.sh) — this header
 * supplies only what Ghidra's decompiler assumes exists:
 *   - typedefs for Ghidra's undefinedN types
 *   - the DAT_/FLOAT_/DOUBLE_/PTR_ globals as macros that dereference the ORIGINAL
 *     GameCube addresses inside wasm linear memory (the "one memory arena at original
 *     addresses" from the design). gen_arena.py populates those addresses from boot.dol
 *     with byte-order converted at generation time (design §4 endianness rule).
 *   - CONCAT44: in every use inside these units it is the PPC int->double bit trick
 *     (0x43300000 magic + subtract 2^52); the (double) cast in Ghidra output denotes
 *     REINTERPRETATION, so it is defined as a union bit-cast, not a value conversion.
 *   - countLeadingZeros: PPC cntlzw semantics (cntlzw(0) == 32; __builtin_clz(0) is UB).
 *   - SDK functions (gnt4_PS*) are left as extern declarations -> wasm env imports,
 *     provided by the TS/JS shim layer (design stage 1: SDK is never ported).
 */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>   /* Ghidra emits `bool` for cr-bit results */
#include <math.h>      /* SQRT, fabs, sqrt */

typedef unsigned char       undefined;
typedef unsigned char       undefined1;
typedef unsigned short      undefined2;
typedef unsigned int        undefined4;
typedef unsigned long long  undefined8;   /* an INTEGER, never double */
typedef unsigned char       byte;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef unsigned long long  ulonglong;
typedef long long           longlong;

/* In these units the (double)CONCAT44(...) idiom is a bit reinterpretation. */
#define CONCAT44(hi, lo) \
  (((union { unsigned long long u; double d; }){ \
     .u = ((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo) }).d)

/* Ghidra emits SQRT(x) for PPC frsqrte / sqrt sequences. On the GameCube this is
 * the hardware reciprocal-sqrt estimate refined by Newton; in wasm we use libm sqrt
 * which matches the mathematical result. It must be DEFINED here (not an import). */
#define SQRT(x)  (sqrt((double)(x)))

/* PPC cntlzw: defined for 0 (returns 32), unlike __builtin_clz. */
static inline uint countLeadingZeros(int x) {
  return x == 0 ? 32u : (uint)__builtin_clz((unsigned int)x);
}

#define ABS(x) fabs((double)(x))

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
extern void   gnt4_PSVECNormalize_bl(float *a, float *out);
extern double gnt4_PSVECMag_bl(float *a);
extern double gnt4_PSVECSquareDistance_bl(float *a, float *b);

#endif /* GNT4_SHIM_H */

/* ---- AUTO-GENERATED (port_unit_generator) ---- */
/* Ghidra `code` for indirect dispatch: unprototyped so any-arg calls
 * compile. Staging units are never executed; address->wasm-table
 * dispatch mapping is a later pipeline stage. */
typedef void (code)();

/* unit-referenced globals + external callees; widths read off call sites. */
#define DOUBLE_80436ab0 GC_F64(0x80436ab0)
#define DOUBLE_80436ab8 GC_F64(0x80436ab8)
#define DOUBLE_80436b30 GC_F64(0x80436b30)
#define FLOAT_80436aa8 GC_F32(0x80436aa8)
#define FLOAT_80436ac4 GC_F32(0x80436ac4)
#define FLOAT_80436acc GC_F32(0x80436acc)
#define FLOAT_80436ae8 GC_F32(0x80436ae8)
#define FLOAT_80436aec GC_F32(0x80436aec)
#define FLOAT_80436b18 GC_F32(0x80436b18)
#define FLOAT_80436b1c GC_F32(0x80436b1c)
#define FLOAT_80436b20 GC_F32(0x80436b20)
#define FLOAT_80436b28 GC_F32(0x80436b28)
#define FLOAT_80436b38 GC_F32(0x80436b38)
#define FLOAT_80436b3c GC_F32(0x80436b3c)
#define FLOAT_80436b40 GC_F32(0x80436b40)
#define FLOAT_80436b44 GC_F32(0x80436b44)
#define FLOAT_80436b48 GC_F32(0x80436b48)
#define PTR_FUN_802c392c GC_PTR(0x802c392c)
#define PTR_FUN_804335b8 GC_PTR(0x804335b8)
#define PTR_FUN_804335c0 GC_PTR(0x804335c0)

extern void FUN_8000ee04(int param_1, int param_2);
extern void FUN_800452e4(double param_1, float *param_2, short param_3);
extern void zz_0010664_(int param_1);
extern void zz_00106fc_(int param_1, int param_2, float *param_3);
extern void zz_00453fc_(char param_1, float *param_2, float *param_3, unsigned int param_4);
