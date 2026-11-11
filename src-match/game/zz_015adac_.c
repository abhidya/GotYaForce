/* MATCHED  zz_015adac_ @ 0x8015adac  (10 instructions)
 *
 *   8015adac  9421fff0  stwu r1, -0x10(r1)
 *   8015adb0  7c0802a6  mflr r0
 *   8015adb4  3c808034  lis r4, -0x7fcc
 *   8015adb8  90010014  stw r0, 0x14(r1)
 *   8015adbc  38844890  addi r4, r4, 0x4890
 *   8015adc0  4801f5b5  bl 0x8017a374
 *   8015adc4  80010014  lwz r0, 0x14(r1)
 *   8015adc8  7c0803a6  mtlr r0
 *   8015adcc  38210010  addi r1, r1, 0x10
 *   8015add0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 588fa224ccb326f3580d9ac518c38f35574ac055f04cdc9b4ea12010d962b1ec
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80344890;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_80344890);
}
