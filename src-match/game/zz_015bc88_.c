/* MATCHED  zz_015bc88_ @ 0x8015bc88  (10 instructions)
 *
 *   8015bc88  9421fff0  stwu r1, -0x10(r1)
 *   8015bc8c  7c0802a6  mflr r0
 *   8015bc90  3c808034  lis r4, -0x7fcc
 *   8015bc94  90010014  stw r0, 0x14(r1)
 *   8015bc98  38845c34  addi r4, r4, 0x5c34
 *   8015bc9c  4801bda1  bl 0x80177a3c
 *   8015bca0  80010014  lwz r0, 0x14(r1)
 *   8015bca4  7c0803a6  mtlr r0
 *   8015bca8  38210010  addi r1, r1, 0x10
 *   8015bcac  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : bde43476fc2b3b5c947d445b49d0d3986598b1850fab2413476616a371116f45
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80345c34;

extern int zz_0177a3c_(int, int);

int f(int p0)
{
    return zz_0177a3c_(p0, &DAT_80345c34);
}
