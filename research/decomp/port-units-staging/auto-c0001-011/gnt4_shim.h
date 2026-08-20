/* gnt4_shim.h — POC stage-2 "header + arena" scaffold (HANDOFF-2026-08-09 §4). */
#ifndef GNT4_SHIM_H
#define GNT4_SHIM_H

#include <stdbool.h>

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

/* PPC int->double magic: reinterpretation. Returns the raw 64-bit bit pattern. */
#define CONCAT44(hi, lo) \
  ((unsigned long long)((unsigned long long)(unsigned int)(hi) << 32) | (unsigned int)(lo))

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

/* constants */
#define FLOAT_80436f68  GC_F32(0x80436f68)
#define FLOAT_80436f78  GC_F32(0x80436f78)
#define FLOAT_80436f7c  GC_F32(0x80436f7c)
#define FLOAT_80436f9c  GC_F32(0x80436f9c)
#define FLOAT_80437024  GC_F32(0x80437024)
#define FLOAT_80437028  GC_F32(0x80437028)
#define DOUBLE_80436fb0 GC_F64(0x80436fb0)
#define DOUBLE_80436f88 GC_F64(0x80436f88)

/* damage-table pointers */
#define PTR_DAT_804335e0 GC_PTR(0x804335e0)
#define PTR_PTR_804335e8 GC_PTR(0x804335e8)
#define PTR_PTR_804335f0 GC_PTR(0x804335f0)
#define PTR_DAT_804335f8 GC_PTR(0x804335f8)
#define PTR_PTR_80433600 GC_PTR(0x80433600)
#define PTR_PTR_80433608 GC_PTR(0x80433608)
#define PTR_PTR_80433610 GC_PTR(0x80433610)
#define PTR_DAT_80433618 GC_PTR(0x80433618)

/* runtime-struct pointers */
#define PTR_DAT_80433930 GC_PTR(0x80433930)
#define PTR_DAT_80433934 GC_PTR(0x80433934)
#define PTR_DAT_80433950 GC_PTR(0x80433950)
#define PTR_DAT_80433954 GC_PTR(0x80433954)
#define DAT_8043625c     GC_IPTR(0x8043625c)

/* bss live-state */
#define DAT_803b069c GC_S16(0x803b069c)
#define DAT_803b068c GC_IPTR(0x803b068c)

/* type-category remap */
#define PTR_DAT_802f2e28 GC_IPTR(0x802f2e28)

/* combo-rank falloff table base */
#define DAT_802c7ca0 GC_U8(0x802c7ca0)

/* Unit B data */
#define DAT_802cffc8 GC_U8(0x802cffc8)
#define DAT_803b0720 GC_F32(0x803b0720)

/* ---- SDK seam ---- */
extern undefined8 gnt4_PSVECSubtract_bl(float *a, float *b, float *out);
extern undefined8 gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double     gnt4_PSQUATDotProduct_bl(float *a, float *b);
extern void       gnt4_PSQUATScale_bl(double s, float *v, float *out);
extern undefined8 gnt4_PSMTXMultVec_bl(float *m, float *v, float *out);
extern undefined8 gnt4_PSMTXTrans_bl(double x, double y, double z, float *out);
extern void       gnt4_PSMTXScale_bl(double x, double y, double z, float *out);
extern undefined8 gnt4_PSMTXConcat_bl(float *a, float *b, float *out);
extern void       gnt4_PSMTXRotRad_bl(double rad, float *out, int axis);

#endif /* GNT4_SHIM_H */

/* ---- AUTO-GENERATED (port_unit_generator) ---- */
typedef void (code)();

#define DAT_802c3b68 GC_U8(0x802c3b68)
#define DAT_802c46a8 GC_F32(0x802c46a8)
#define _DAT_802c46a8 GC_F32(0x802c46a8)
#define DAT_802c46ac GC_F32(0x802c46ac)
#define _DAT_802c46ac GC_F32(0x802c46ac)
#define DAT_802c46b8 GC_U8(0x802c46b8)
#define DAT_802c46bc GC_U8(0x802c46bc)
#define DAT_802c46c0 GC_U8(0x802c46c0)
#define fRam802c46cc GC_F32(0x802c46cc)
#define DAT_803c4e84 GC_U8(0x803c4e84)
#define DAT_803c7422 GC_U8(0x803c7422)
#define DAT_804361fc GC_IPTR(0x804361fc)

/* Function pointers (defined as stubs to satisfy linker gate) */
void FUN_80012274(int param_1);
void FUN_80047aa4(int param_1);

#define DOUBLE_80436bd0 GC_F64(0x80436bd0)
#define DOUBLE_80436c00 GC_F64(0x80436c00)
#define DOUBLE_80436c08 GC_F64(0x80436c08)

#define FLOAT_80436bc4 GC_F32(0x80436bc4)
#define FLOAT_80436bc8 GC_F32(0x80436bc8)
#define FLOAT_80436bcc GC_F32(0x80436bcc)
#define FLOAT_80436bd8 GC_F32(0x80436bd8)
#define FLOAT_80436bdc GC_F32(0x80436bdc)
#define FLOAT_80436be0 GC_F32(0x80436be0)
#define FLOAT_80436be4 GC_F32(0x80436be4)
#define FLOAT_80436be8 GC_F32(0x80436be8)
#define FLOAT_80436bec GC_F32(0x80436bec)
#define FLOAT_80436bf0 GC_F32(0x80436bf0)
#define FLOAT_80436bf4 GC_F32(0x80436bf4)
#define FLOAT_80436bf8 GC_F32(0x80436bf8)
#define FLOAT_80436bfc GC_F32(0x80436bfc)
#define FLOAT_80436c10 GC_F32(0x80436c10)
#define FLOAT_80436c14 GC_F32(0x80436c14)
#define FLOAT_80436c18 GC_F32(0x80436c18)
#define FLOAT_80436c1c GC_F32(0x80436c1c)
#define FLOAT_80436c20 GC_F32(0x80436c20)
#define FLOAT_80436c24 GC_F32(0x80436c24)
#define FLOAT_80436c28 GC_F32(0x80436c28)
#define FLOAT_80436c2c GC_F32(0x80436c2c)
#define FLOAT_80436c30 GC_F32(0x80436c30)
#define FLOAT_80436c34 GC_F32(0x80436c34)

extern undefined8 zz_0006fb4_(double, double, double, double, double, double, double, double, int, int, int, int, int, int, int, int);
extern undefined8 zz_00076d0_(undefined8, double, double, double, double, double, double, double, int, float *, undefined *, undefined4, undefined4, undefined4, undefined4, undefined4);
extern undefined8 zz_0007834_(undefined8, double, double, double, double, double, double, double, int, float *, char *, undefined *, undefined4, undefined4, undefined4, undefined4);
extern undefined8 zz_0007c30_(undefined8, double, double, double, double, double, double, double, int, undefined4, float *, uint, undefined4, undefined4, undefined4, undefined4);
extern undefined8 zz_0007cac_(double, int);
extern void       zz_0007cd0_(int, int, int, int);
extern void       zz_0008614_(double, double, double, double, double, double, double, double, int, int, float *, uint, undefined4, undefined4, undefined4, undefined4);
extern undefined8 zz_00086b8_(double, double, double, double, double, double, double, double, int, int, float *, uint, undefined4, undefined4, undefined4, undefined4);
extern void       zz_0009958_(int, int);
extern int        zz_0011ce0_(int);
extern void       zz_0089100_(int, int, int);
extern undefined8 zz_020b4ac_(double, double, double, float *, float *);
extern void       zz_020b520_(double, double, double, float *, float *);

/* Stubs for FUN_80012274 and FUN_80047aa4 to satisfy linker gate */
void FUN_80012274(int param_1) { (void)param_1; }
void FUN_80047aa4(int param_1) { (void)param_1; }
