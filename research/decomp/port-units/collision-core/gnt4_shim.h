/* gnt4_shim_collision.h — scaffold header seed for the collision-core wasm unit.
 *
 * Superset of the POC gnt4_shim.h conventions (same typedefs/GC_xxx arena-macro
 * design) plus the collision-pass data macros, SDK externs, and the STRUCTURAL
 * STUBS this unit is oracled with. The ported .c bodies are verbatim extractions
 * (collision_hit_pair_pass_active_vs_borgs chunk_0003.c:7026-7164,
 * _active_vs_secondary 7168-7306, _object_lists 7310-7426); this header supplies
 * only what Ghidra's decompiler assumes exists.
 *
 * STRUCTURAL-ORACLE CONTRACT (mirrored exactly by harness-collision.mjs and its
 * TS-side SourceCollisionHooks): the four unsurfaced hitbox-shape functions
 * (zz_002fd7c_ broad-phase, zz_0039f6c_ shape compat, zz_0030348_ transform,
 * zz_0030490_ overlap) and the per-pair resolver
 * resolve_hitbox_target_effects_and_damage are NOT ported here — they are
 * defined below as deterministic stubs so the verbatim PASS code (filter chains,
 * immediate-vs-deferred, closest-target search, deferred nudge, delegation
 * order) is what the oracle actually gates:
 *   - zz_002fd7c_ / zz_0039f6c_  -> admit all (TS defaultSourceCollisionHooks).
 *   - zz_0030348_ -> contact point DAT_803b0720 := the copied target+0x64 vec
 *     (globals at matB+0xc, already populated by the pass's own copy loops).
 *   - zz_0030490_ -> overlap := the copied target+0x78 flag byte (matB+0x20),
 *     harness-encoded per target.
 *   - resolver stub -> appends (active, target, DAT_803b0720 vec) to the pair
 *     log at GC 0x80630000 (u32 count, then 20-byte records) and mutates
 *     nothing, so pair FORMATION order/identity is byte-comparable.
 * Constants are DOL-sourced via gen_arena_collision.py (arena-collision.json).
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
typedef void code();  /* +0x100 callback slots; harness keeps them NULL */

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
#define GC_U16(a)  (*(unsigned short *)(unsigned int)(a))
#define GC_U32(a)  (*(unsigned int *)(unsigned int)(a))
#define GC_S16(a)  (*(short *)(unsigned int)(a))
#define GC_PTR(a)  (*(char **)(unsigned int)(a))
#define GC_IPTR(a) (*(int *)(unsigned int)(a))

/* constants (sec12 .sdata2, DOL-initialized; values populated from arena) */
#define FLOAT_80436f68  GC_F32(0x80436f68)  /* 0.0  nudge |v|^2 epsilon gate    */
#define FLOAT_80436f7c  GC_F32(0x80436f7c)  /* 0.5  nudge half-scale            */
#define FLOAT_80436f98  GC_F32(0x80436f98)  /* 4e8  deferred-search sentinel    */

/* object lists: arrays of battle-object pointers (int per slot), harness-built */
#define DAT_803c477c  GC_IPTR(0x803c477c)   /* active list (passes 1+2)         */
#define DAT_803c2f7c  GC_IPTR(0x803c2f7c)   /* borg roster (pass 1 targets)     */
#define DAT_803c417c  GC_IPTR(0x803c417c)   /* secondary list (pass 2 targets)  */
#define DAT_803c177c  GC_IPTR(0x803c177c)   /* object list A (pass 3 actives)   */
#define DAT_803c117c  GC_IPTR(0x803c117c)   /* object list B (pass 3 targets)   */

/* list counts (u16, .sbss; harness-written per case) */
#define DAT_80436250  GC_U16(0x80436250)    /* active count                     */
#define DAT_80436248  GC_U16(0x80436248)    /* borg count                       */
#define DAT_8043624e  GC_U16(0x8043624e)    /* secondary count                  */
#define DAT_80436240  GC_U16(0x80436240)    /* object list A count              */
#define DAT_8043623e  GC_U16(0x8043623e)    /* object list B count              */

/* transform-global blocks: the pass copy loops write active+0x58.. to
 * 0x803b04d0.. and target+0x58.. to 0x803b0368.. (0x2d pairs = 360 bytes).
 * The named u8 slots below are only address-taken by the verbatim code. */
#define DAT_803b0364  GC_U8(0x803b0364)     /* target block base - 4            */
#define DAT_803b0368  GC_U8(0x803b0368)     /* target block (== target+0x58)    */
#define DAT_803b0374  GC_U8(0x803b0374)     /* target block +0xc (target+0x64)  */
#define DAT_803b04d0  GC_U8(0x803b04d0)     /* active block (== active+0x58)    */
#define DAT_803b0504  GC_U8(0x803b0504)     /* active block +0x34 (active+0x8c) */

/* contact point (vec3 of u32-typed words in the verbatim code) */
#define DAT_803b0720  GC_U32(0x803b0720)
#define DAT_803b0724  GC_U32(0x803b0724)
#define DAT_803b0728  GC_U32(0x803b0728)

/* ---- SDK seam (design stage 1): never ported, resolved as wasm env imports ---- */
extern void   gnt4_PSVECSubtract_bl(float *a, float *b, float *out);
extern void   gnt4_PSVECAdd_bl(float *a, float *b, float *out);
extern double gnt4_PSVECSquareMag_bl(float *v);
extern double gnt4_PSVECSquareDistance_bl(float *a, float *b);
extern void   gnt4_PSQUATScale_bl(double s, float *v, float *out);

/* ---- structural stubs (contract documented in the file header) ---- */

/* zz_002fd7c_ broad-phase bounding test: admit all (category 0x40 or 2). */
static int zz_002fd7c_(int active, int target, int category) {
  (void)active; (void)target; (void)category;
  return 1;
}

/* zz_0039f6c_ shape-TYPE compatibility test: admit all. */
static int zz_0039f6c_(int active_shape_ptr, int target_shape_ptr) {
  (void)active_shape_ptr; (void)target_shape_ptr;
  return 1;
}

/* zz_0030348_ transform: the real ROM transforms both hitbox blocks and writes
 * the contact point; the stub writes DAT_803b0720 := the copied target+0x64 vec
 * (matB+0xc..), which the pass's own copy loop just populated. */
static void zz_0030348_(unsigned char *matA, unsigned char *matB,
                        int active_shape, int target_shape) {
  (void)matA; (void)active_shape; (void)target_shape;
  DAT_803b0720 = *(unsigned int *)(matB + 0x0c);
  DAT_803b0724 = *(unsigned int *)(matB + 0x10);
  DAT_803b0728 = *(unsigned int *)(matB + 0x14);
}

/* zz_0030490_ overlap test: the copied target+0x78 flag byte (matB+0x20),
 * harness-encoded per target; selector kept for signature fidelity. */
static int zz_0030490_(unsigned char *matA, unsigned char *matB, int selector) {
  (void)matA; (void)selector;
  return matB[0x20];
}

/* resolver stub: append (active, target, contact point) to the pair log.
 * Layout at 0x80630000: [u32 count][20-byte records: u32 active, u32 target,
 * u32 cp.x bits, u32 cp.y bits, u32 cp.z bits]. Mutates nothing else. */
#define GC_COLLISION_PAIRLOG 0x80630000u
static void resolve_hitbox_target_effects_and_damage(int active, int target) {
  unsigned int n = GC_U32(GC_COLLISION_PAIRLOG);
  unsigned int rec = GC_COLLISION_PAIRLOG + 4u + n * 20u;
  GC_U32(rec + 0x00) = (unsigned int)active;
  GC_U32(rec + 0x04) = (unsigned int)target;
  GC_U32(rec + 0x08) = DAT_803b0720;
  GC_U32(rec + 0x0c) = DAT_803b0724;
  GC_U32(rec + 0x10) = DAT_803b0728;
  GC_U32(GC_COLLISION_PAIRLOG) = n + 1u;
}

#endif /* GNT4_SHIM_H */
