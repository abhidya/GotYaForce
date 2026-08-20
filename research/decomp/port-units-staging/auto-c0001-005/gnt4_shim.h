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

#include <stdbool.h>  /* Ghidra emits `bool` for cr-bit results */
#include <math.h>     /* sqrt, fabs */

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

/* In these units undefined8 is only ever used as a double (the CONCAT44 fp trick). */
/* typedef double undefined8; -- replaced by integer typedef above per spec */

/* PPC int->double magic: the (double)CONCAT44(...) idiom is a bit reinterpretation. */
#define CONCAT44(hi, lo) \
  (((union { unsigned long long u; double d; }){ \
     .u = ((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo) }).d)

/* PPC cntlzw: defined for 0 (returns 32), unlike __builtin_clz. */
static inline uint countLeadingZeros(int x) {
  return x == 0 ? 32u : (uint)__builtin_clz((unsigned int)x);
}

#define ABS(x) __builtin_fabs(x)

/* Ghidra SQRT helper: PPC sqrt semantics, defined for all inputs. */
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

/* Additional SDK functions referenced by this unit */
extern void   gnt4_PSVECCrossProduct_bl(float *a, float *b, float *out);
extern void   gnt4_PSVECNormalize_bl(float *a, float *out);
extern double gnt4_PSVECSquareMag_bl(float *a);

#endif /* GNT4_SHIM_H */

/* ---- AUTO-GENERATED (port_unit_generator) ---- */
/* Ghidra `code` for indirect dispatch: unprototyped so any-arg calls
 * compile. Staging units are never executed; address->wasm-table
 * dispatch mapping is a later pipeline stage. */
typedef void (code)();

/* unit-referenced globals + external callees; widths are prefix-derived defaults
 * (the compile-fix loop may refine them). */
#define DAT_803c4e84 GC_U8(0x803c4e84)
#define DAT_803c4e88 GC_U8(0x803c4e88)
#define DAT_803c4e8c GC_U8(0x803c4e8c)
#define DAT_803c4e90 GC_U8(0x803c4e90)
#define DAT_803c4e94 GC_U8(0x803c4e94)
#define DAT_803c4e98 GC_U8(0x803c4e98)
#define DAT_803c7204 GC_U8(0x803c7204)
#define DOUBLE_80436ab0 GC_F64(0x80436ab0)
#define DOUBLE_80436ab8 GC_F64(0x80436ab8)
#define FLOAT_80436aa8 GC_F32(0x80436aa8)
#define FLOAT_80436ac0 GC_F32(0x80436ac0)
#define FLOAT_80436ac4 GC_F32(0x80436ac4)
#define FLOAT_80436acc GC_F32(0x80436acc)
#define FLOAT_80436ad0 GC_F32(0x80436ad0)
#define FLOAT_80436ad4 GC_F32(0x80436ad4)
#define FLOAT_80436ae8 GC_F32(0x80436ae8)
#define FLOAT_80436b0c GC_F32(0x80436b0c)
#define FLOAT_80436b18 GC_F32(0x80436b18)
#define FLOAT_80436b1c GC_F32(0x80436b1c)
#define FLOAT_80436b38 GC_F32(0x80436b38)
#define FLOAT_80436b40 GC_F32(0x80436b40)
#define FLOAT_80436b44 GC_F32(0x80436b44)
#define FLOAT_80436b58 GC_F32(0x80436b58)
#define FLOAT_80436b5c GC_F32(0x80436b5c)
#define FLOAT_80436b60 GC_F32(0x80436b60)
#define FLOAT_80436b64 GC_F32(0x80436b64)
#define FLOAT_80436b68 GC_F32(0x80436b68)
#define FLOAT_80436b6c GC_F32(0x80436b6c)
#define FLOAT_80436b70 GC_F32(0x80436b70)
#define FLOAT_80436b74 GC_F32(0x80436b74)
#define PTR_FUN_804335d8 GC_PTR(0x804335d8)

/* External function declarations with correct signatures from call sites */
extern void FUN_8004503c(double param_1, float *param_2, float *param_3, float *param_4);
extern void FUN_800450e0(double param_1, double param_2, float *param_3, float *param_4, float *param_5);
extern void FUN_801fe050(int param_1);
extern void FUN_801fe134(void);
extern double zz_0045204_(short param_1);
extern double zz_0045238_(short param_1);
extern double zz_004526c_(short param_1);
