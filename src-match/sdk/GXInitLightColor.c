/* MATCHED  gnt4-GXInitLightColor-bl @ 0x802285f4  (3 instructions)
 *
 *   802285f4  80040000  lwz r0, 0(r4)
 *   802285f8  9003000c  stw r0, 0xc(r3)
 *   802285fc  4e800020  blr
 *
 * ---------------------------------------------------------------------------
 * PROVENANCE -- READ THIS BEFORE REUSING ANYTHING IN THIS DIRECTORY.
 *
 * The private `__GXLightObjInt_struct` layout below is taken from
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
 * WHAT THIS FILE IS, AND WHAT IT IS NOT.
 *
 * The genuine CC0 source body is:
 *
 *     void GXInitLightColor(GXLightObj* lt_obj, GXColor color) {
 *         __GXLightObjInt_struct* obj;
 *         ASSERTMSGLINE(462, lt_obj != NULL, "Light Object Pointer is null");
 *         obj = (__GXLightObjInt_struct*)lt_obj;
 *         CHECK_GXBEGIN(463, "GXInitLightColor");
 *         *(u32*)&obj->Color = *(u32*)&color;
 *     }
 *
 * That body DOES NOT COMPILE under mwcc-rs: taking the address of a
 * by-reference struct parameter (`&color`) makes it spill the incoming
 * pointer to a stack home and reload it, which real MWCC does not do, and
 * `*(u32*)&obj->Color` is rejected outright ("pointer leaf access needs a
 * pointer variable (roadmap)").  Both diagnostics are reproduced verbatim in
 * the spike doc.
 *
 * So this file is a REWRITE that reaches the same three retail instructions
 * through the subset mwcc-rs implements.  It proves the retail bytes are
 * reachable; it does NOT prove the free SDK path works end to end, because
 * the blocker there is the compiler, not the source.  Treat it accordingly.
 *
 * Iterations to match: 1 for the rewrite; the genuine source is at 0 of 2
 * attempts and is blocked by a compiler capability gap, not by the C.
 */

typedef unsigned int u32;

typedef struct GXLightObj {
    u32 dummy[16];
} GXLightObj;

typedef struct __GXLightObjInt_struct {
    u32   reserved[3];
    u32   Color;
    float a[3];
    float k[3];
    float lpos[3];
    float ldir[3];
} __GXLightObjInt_struct;

void f(GXLightObj *lt_obj, u32 *color)
{
    ((__GXLightObjInt_struct *)lt_obj)->Color = *color;
}
