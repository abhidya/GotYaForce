/* MATCHED  zz_02647e8_ @ 0x802647e8  (9 instructions)
 *
 *   802647e8  9421fff0  stwu r1, -0x10(r1)
 *   802647ec  7c0802a6  mflr r0
 *   802647f0  90010014  stw r0, 0x14(r1)
 *   802647f4  80630004  lwz r3, 4(r3)
 *   802647f8  48003c7d  bl 0x80268474
 *   802647fc  80010014  lwz r0, 0x14(r1)
 *   80264800  7c0803a6  mtlr r0
 *   80264804  38210010  addi r1, r1, 0x10
 *   80264808  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4fabf6df675bff4f551d1ac3a626f31de0125357b37c80a7f4356d0aae72c42f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_0268474_(int);

int f(S0 *p0)
{
    return zz_0268474_(p0->field_4);
}
