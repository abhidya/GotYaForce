/* MATCHED  zz_015c560_ @ 0x8015c560  (10 instructions)
 *
 *   8015c560  9421fff0  stwu r1, -0x10(r1)
 *   8015c564  7c0802a6  mflr r0
 *   8015c568  3c808034  lis r4, -0x7fcc
 *   8015c56c  90010014  stw r0, 0x14(r1)
 *   8015c570  38846278  addi r4, r4, 0x6278
 *   8015c574  4801de01  bl 0x8017a374
 *   8015c578  80010014  lwz r0, 0x14(r1)
 *   8015c57c  7c0803a6  mtlr r0
 *   8015c580  38210010  addi r1, r1, 0x10
 *   8015c584  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b8f575d436f2b1b44be2f956886f9abfe329ab95fcc9856f202a1354ca597ced
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80346278;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_80346278);
}
