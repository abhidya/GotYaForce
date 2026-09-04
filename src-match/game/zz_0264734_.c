/* MATCHED  zz_0264734_ @ 0x80264734  (9 instructions)
 *
 *   80264734  9421fff0  stwu r1, -0x10(r1)
 *   80264738  7c0802a6  mflr r0
 *   8026473c  90010014  stw r0, 0x14(r1)
 *   80264740  80630004  lwz r3, 4(r3)
 *   80264744  48003ca1  bl 0x802683e4
 *   80264748  80010014  lwz r0, 0x14(r1)
 *   8026474c  7c0803a6  mtlr r0
 *   80264750  38210010  addi r1, r1, 0x10
 *   80264754  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : af7522f311a2f19800da645d0b4d2d3f9ff3bc3d6ab95e3ac0891eb841070aad
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683e4_(int);

int f(S0 *p0)
{
    return zz_02683e4_(p0->field_4);
}
