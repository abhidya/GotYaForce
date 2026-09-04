/* MATCHED  zz_0264758_ @ 0x80264758  (9 instructions)
 *
 *   80264758  9421fff0  stwu r1, -0x10(r1)
 *   8026475c  7c0802a6  mflr r0
 *   80264760  90010014  stw r0, 0x14(r1)
 *   80264764  80630004  lwz r3, 4(r3)
 *   80264768  48003c85  bl 0x802683ec
 *   8026476c  80010014  lwz r0, 0x14(r1)
 *   80264770  7c0803a6  mtlr r0
 *   80264774  38210010  addi r1, r1, 0x10
 *   80264778  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : f1aaa72b22d34e9929b13abc895602aad74a9c68c6c5a6f5ecd68b08290cdefe
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683ec_(int);

int f(S0 *p0)
{
    return zz_02683ec_(p0->field_4);
}
