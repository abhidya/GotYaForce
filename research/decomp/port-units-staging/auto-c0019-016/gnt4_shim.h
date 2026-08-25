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
#define DAT_80301cf0 GC_U8(0x80301cf0)
#define DAT_803bb470 GC_U8(0x803bb470)
#define DAT_803c7380 GC_U8(0x803c7380)
#define FLOAT_80438604 GC_F32(0x80438604)
#define FLOAT_80438608 GC_F32(0x80438608)
#define FLOAT_8043860c GC_F32(0x8043860c)
#define FLOAT_80438610 GC_F32(0x80438610)
#define PTR_DAT_80433940 GC_PTR(0x80433940)
extern int zz_00ff618_(void);  /* return refined: caller assigns to `int iVar1` (line 43) */
extern undefined8 zz_00088a4_(double param_1,double param_2,double param_3,double param_4,double param_5,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);  /* return refined: assigned to `undefined8 uVar3` (line 89) */
extern undefined8 zz_0008970_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);  /* return refined: assigned to `undefined8 uVar3` (line 91) */
extern undefined8 zz_0005984_(undefined4 param_1);  /* return refined: caller assigns to `undefined8 uVar1` (line 116) */
extern void zz_0008924_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0008948_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,double param_6,double param_7,double param_8,float *param_9,undefined4 param_10,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0008b58_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0008cf4_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0040910_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern undefined8 zz_0040b94_(void);  /* return refined: assigned to `undefined8 uVar1` (line 116) */
extern void zz_0087814_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0087cf0_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0089554_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0089658_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0089898_(uint param_1);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_0089c00_(int param_1);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_008a16c_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_008c0dc_(undefined4 param_1);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_008c104_(undefined4 param_1);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_008c12c_(undefined4 param_1);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_01978d0_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_01ae8a8_(void);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern void zz_01b1f10_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);  /* OWNER PROTOTYPE (oracle-registry.json): do not alter */
extern int zz_01b1fb8_(void);  /* return refined: caller assigns to `int iVar1` (line 43) */

/* ---- owner prototypes (auto-injected from oracle-registry.json) ---- */
extern void FUN_80089eb4(void);
extern void FUN_80089f28(void);
extern void FUN_80089f9c(void);

/* cCameraManager__HasCamera_cBaseCamera: game logic (not gnt4_* SDK), must be
 * defined here with correct PowerPC semantics. Called at line 95 in unit.c with
 * 16 args, result ignored (void). The call is a tail-call to a camera manager
 * method; on the GameCube this is a real function. For staging units we provide
 * a stub that preserves the calling convention. */
void cCameraManager__HasCamera_cBaseCamera(undefined8 param_1,double param_2,double param_3,
                                           double param_4,double param_5,double param_6,
                                           double param_7,double param_8,undefined4 *param_9,
                                           undefined4 param_10,undefined *param_11,
                                           undefined4 param_12,undefined4 param_13,
                                           undefined4 param_14,undefined4 param_15,
                                           undefined4 param_16) {
  (void)param_1; (void)param_2; (void)param_3; (void)param_4; (void)param_5;
  (void)param_6; (void)param_7; (void)param_8; (void)param_9; (void)param_10;
  (void)param_11; (void)param_12; (void)param_13; (void)param_14; (void)param_15;
  (void)param_16;
}
