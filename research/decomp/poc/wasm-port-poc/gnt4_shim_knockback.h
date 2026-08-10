/* gnt4_shim_knockback.h — scaffold header seed for the knockback-core wasm unit.
 *
 * Superset of the POC gnt4_shim.h (same POC-validated CONCAT44/cntlzw/ABS/typedef
 * definitions) plus the knockback-unit data macros and SDK externs. The ported .c
 * bodies are verbatim extractions (zz_00300bc_ chunk_0003.c:8540-8627,
 * FUN_800452a0 chunk_0005.c:2191-2204, zz_005ec20_ chunk_0007.c:5544-5574);
 * this header supplies only what Ghidra's decompiler assumes exists.
 * Constants are DOL-sourced via gen_arena_knockback.py (arena-knockback.json).
 */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>  /* Ghidra emits `bool` for cr-bit results */

typedef unsigned char undefined;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;

/* In these units undefined8 is only ever used as a double (the CONCAT44 fp trick). */
typedef double undefined8;

/* PPC int->double magic: the (double)CONCAT44(...) idiom is a bit reinterpretation. */
#define CONCAT44(hi, lo) \
  (((union { unsigned long long u; double d; }){ \
     .u = ((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo) }).d)

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

/* constants (sec12 .sdata2, DOL-initialized; values populated from arena) */
#define FLOAT_80436f68  GC_F32(0x80436f68)  /* 0.0  zero / mode-fallback gate      */
#define FLOAT_80436f74  GC_F32(0x80436f74)  /* -1.0 degenerate fallback Z          */
#define FLOAT_80436fc0  GC_F32(0x80436fc0)  /* 0.01 degenerate |v|^2 threshold     */
#define FLOAT_8043707c  GC_F32(0x8043707c)  /* 65536/(2*pi) radians -> BAM16       */
#define FLOAT_80437440  GC_F32(0x80437440)  /* zz_005ec20_ scale-ratio bias        */
#define FLOAT_80437444  GC_F32(0x80437444)  /* zz_005ec20_ vertical seed           */
#define FLOAT_80437490  GC_F32(0x80437490)  /* zz_005ec20_ deceleration divisor    */

/* knockback ground horizontal-speed table (byte-addressed in source:
 * *(float *)(&DAT_802dd8a0 + strength * 4) — 16 f32 entries, s*7.0) */
#define DAT_802dd8a0 GC_U8(0x802dd8a0)

/* ---- SDK seam (design stage 1): never ported, resolved as wasm env imports ---- */
extern void   gnt4_PSVECSubtract_bl(float *a, float *b, float *out);
extern void   gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSVECMag_bl(float *v);
extern double gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern void   gnt4_PSQUATScale_bl(double s, float *v, float *out);
extern double gnt4_atan2_bl(double y, double x);

#endif /* GNT4_SHIM_H */
