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
 *   - CONCAT44: pure integer bit-manipulation producing an unsigned long long.
 *   - countLeadingZeros: PPC cntlzw semantics (cntlzw(0) == 32; __builtin_clz(0) is UB).
 *   - SDK functions (gnt4_PS*) are left as extern declarations -> wasm env imports,
 *     provided by the TS/JS shim layer (design stage 1: SDK is never ported).
 */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>  /* Ghidra emits `bool` for cr-bit results */

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

/* CONCAT44 is pure integer bit manipulation. It returns an integer. */
#define CONCAT44(hi, lo) \
  (((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo))

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
extern void   gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern void   gnt4_PSQUATScale_bl(double s, float *v, float *out);

#endif /* GNT4_SHIM_H */

/* ---- AUTO-GENERATED (port_unit_generator) ---- */
/* Ghidra `code` for indirect dispatch: unprototyped so any-arg calls
 * compile. Staging units are never executed; address->wasm-table
 * dispatch mapping is a later pipeline stage. */
typedef void (code)();

/* unit-referenced globals + external callees; widths are prefix-derived defaults
 * (the compile-fix loop may refine them). */

/* DAT_802b0994, etc. are used as undefined4 in local assignments */
#define DAT_802b0994 GC_IPTR(0x802b0994)
#define DAT_802b0998 GC_IPTR(0x802b0998)
#define DAT_802b099c GC_IPTR(0x802b099c)

/* DAT_804361fc is used as an int parameter in calls */
#define DAT_804361fc GC_IPTR(0x804361fc)

#define DOUBLE_80436bd0 GC_F64(0x80436bd0)
#define DOUBLE_80436c00 GC_F64(0x80436c00)
#define DOUBLE_80436c08 GC_F64(0x80436c08)

#define FLOAT_80436bc4 GC_F32(0x80436bc4)
#define FLOAT_80436bcc GC_F32(0x80436bcc)
#define FLOAT_80436c30 GC_F32(0x80436c30)
#define FLOAT_80436c44 GC_F32(0x80436c44)
#define FLOAT_80436cac GC_F32(0x80436cac)
#define FLOAT_80436cb0 GC_F32(0x80436cb0)
#define FLOAT_80436cb4 GC_F32(0x80436cb4)
#define FLOAT_80436cb8 GC_F32(0x80436cb8)
#define FLOAT_80436cbc GC_F32(0x80436cbc)

/* External function prototypes based on call sites */
extern undefined8 zz_0006fb4_(undefined8 param_1, double param_2, double param_3, double param_4, double param_5,
                              double param_6, double param_7, double param_8, int param_9, int param_10,
                              int param_11, short *param_12, undefined4 param_13, undefined4 param_14,
                              undefined4 param_15, undefined4 param_16);

extern undefined8 zz_0007ae4_(undefined8 param_1, double param_2, double param_3, double param_4, double param_5,
                              double param_6, double param_7, double param_8, int param_9, void *param_10,
                              char *param_11, short *param_12, undefined4 param_13, undefined4 param_14,
                              undefined4 param_15, undefined4 param_16);

extern undefined8 zz_00086b8_(double param_1, double param_2, double param_3, double param_4, double param_5,
                              double param_6, double param_7, double param_8, int param_9, int param_10,
                              float *param_11, short *param_12, undefined4 param_13, undefined4 param_14,
                              undefined4 param_15, undefined4 param_16);

extern undefined8 zz_0007c30_(undefined8 param_1, double param_2, double param_3, double param_4, double param_5,
                              double param_6, double param_7, double param_8, int param_9, undefined4 param_10,
                              float *param_11, short *param_12, undefined4 param_13, undefined4 param_14,
                              undefined4 param_15, undefined4 param_16);

extern undefined8 zz_0007908_(double param_1, double param_2, double param_3, double param_4, double param_5,
                              double param_6, double param_7, double param_8, int param_9, float *param_10,
                              float *param_11, int param_12, undefined4 param_13, undefined4 param_14,
                              undefined4 param_15, undefined4 param_16);

extern undefined8 zz_0007834_(undefined8 param_1, double param_2, double param_3, double param_4, double param_5,
                              double param_6, double param_7, double param_8, int param_9, float *param_10,
                              char *param_11, int param_12, undefined4 param_13, undefined4 param_14,
                              undefined4 param_15, undefined4 param_16);

extern double zz_0045238_(short param_1);

extern void zz_0007cd0_(int param_1, int param_2, char *param_3, int param_4);

extern double zz_0007cac_(double param_1, int param_2);

extern void zz_0007a60_(double param_1, double param_2, double param_3, double param_4, double param_5,
                        double param_6, double param_7, double param_8, int param_9, undefined4 *param_10,
                        char *param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14,
                        undefined4 param_15, undefined4 param_16);

extern void zz_0007988_(double param_1, double param_2, double param_3, double param_4, double param_5,
                        double param_6, double param_7, double param_8, int param_9, undefined4 *param_10,
                        char *param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14,
                        undefined4 param_15, undefined4 param_16);
