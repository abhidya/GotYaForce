/* MATCHED  zz_015c510_ @ 0x8015c510  (10 instructions)
 *
 *   8015c510  9421fff0  stwu r1, -0x10(r1)
 *   8015c514  7c0802a6  mflr r0
 *   8015c518  3c808034  lis r4, -0x7fcc
 *   8015c51c  90010014  stw r0, 0x14(r1)
 *   8015c520  38846260  addi r4, r4, 0x6260
 *   8015c524  4801de51  bl 0x8017a374
 *   8015c528  80010014  lwz r0, 0x14(r1)
 *   8015c52c  7c0803a6  mtlr r0
 *   8015c530  38210010  addi r1, r1, 0x10
 *   8015c534  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5c010e8388c940b4ed21bbe589f9d5db0e7fd881cc5f7ac7f0f9fb963302f274
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80346260;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_80346260);
}
