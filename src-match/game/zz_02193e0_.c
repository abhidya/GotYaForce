/* MATCHED  zz_02193e0_ @ 0x802193e0  (3 instructions)
 *
 *   802193e0  3c60803e  lis r3, -0x7fc2
 *   802193e4  3863fbe0  addi r3, r3, -0x420
 *   802193e8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi blr
 *   exact_bytes      : false
 *   source sha256    : da360ea589062f3931bde880ef4ca83b87cb67b2d2a428727cfad52b2db89e1f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803dfbe0;

int f(void)
{
    return &DAT_803dfbe0;
}
