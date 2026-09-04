/* MATCHED  gnt4-GXInitLightColor-bl @ 0x802285f4  (3 instructions)
 *
 *   802285f4  80040000  lwz r0, 0(r4)
 *   802285f8  9003000c  stw r0, 0xc(r3)
 *   802285fc  4e800020  blr
 *
 * ---------------------------------------------------------------------------
 * PROVENANCE -- READ THIS BEFORE REUSING ANYTHING IN THIS DIRECTORY.
 *
 * The struct layout and the function body below are the genuine source from
 * `libs/dolphin/src/gx/GXLight.c` in github.com/zeldaret/tp, which carries a
 * CC0-1.0 dedication at its repository root with no per-directory carve-out.
 * CC0 dedicates the contributors' OWN rights; it cannot dedicate rights they
 * never held, and the underlying work is a decompilation of Nintendo's
 * proprietary Dolphin SDK.  That caveat applies to every public SDK decomp
 * and is not specific to this file.  It is recorded, not resolved.
 *
 * `doldecomp/dolsdk2004`, which the spike named as the SDK source to take,
 * has NO LICENSE FILE AT ALL.  It must not be vendored.  See the spike doc
 * section 5.3.
 *
 * ---------------------------------------------------------------------------
 * WHAT THIS FILE IS.
 *
 * On 2026-09-03 this file was a REWRITE, because the genuine body did not
 * compile.  It does now, and this is that body, matching the retail bytes as
 * written -- so the free-SDK path of spike doc section 5.3 is proven end to end
 * on this function, not merely argued.
 *
 * The two refusals it used to hit were the same mistake twice: mwcc-rs read
 * `*(u32 *)&X` as an address computation rather than as a re-typing of storage
 * that already has an address.
 *
 *   *(u32 *)&obj->Color   ->  "pointer leaf access needs a pointer variable
 *                              (roadmap)" -- refused outright.
 *   *(u32 *)&color        ->  compiled, but gave the by-REFERENCE struct
 *                              parameter a stack home and emitted
 *                              `stwu; stw r3,8(r1); lwz r3,8(r1); addi r1; blr`
 *                              -- a spill and reload of a pointer already in a
 *                              register.  Real MWCC does neither.
 *
 * This project's fork normalises `*(T *)&aggregate` into an ordinary T-typed
 * member access at the aggregate's own offset before lowering, which is what
 * makes both sides collapse to the retail `lwz` / `stw` pair with the 0xc
 * folded into the store displacement.  See
 * research/tools/matching-decomp/mwcc_fork.py, the module
 * `punned_aggregate_access.rs`, and TOOLCHAIN.md section 5.
 *
 * The ASSERTMSGLINE / CHECK_GXBEGIN macros of the original compile to nothing
 * in a release build and are shown, commented, where they stood.
 *
 * Iterations to match: 1, on the genuine source, once the compiler could take
 * it.  It was 0 of 2 before that, and the blocker was never the C.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct GXLightObj {
    u32 dummy[16];
} GXLightObj;

typedef struct __GXLightObjInt_struct {
    u32     reserved[3];
    GXColor Color;
    float   a[3];
    float   k[3];
    float   lpos[3];
    float   ldir[3];
} __GXLightObjInt_struct;

void f(GXLightObj *lt_obj, GXColor color)
{
    __GXLightObjInt_struct *obj;
    /* ASSERTMSGLINE(462, lt_obj != NULL, "Light Object Pointer is null"); */
    obj = (__GXLightObjInt_struct *)lt_obj;
    /* CHECK_GXBEGIN(463, "GXInitLightColor"); */
    *(u32 *)&obj->Color = *(u32 *)&color;
}
