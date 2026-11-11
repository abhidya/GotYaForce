/* MATCHED  zz_015b814_ @ 0x8015b814  (10 instructions)
 *
 *   8015b814  9421fff0  stwu r1, -0x10(r1)
 *   8015b818  7c0802a6  mflr r0
 *   8015b81c  3c808034  lis r4, -0x7fcc
 *   8015b820  90010014  stw r0, 0x14(r1)
 *   8015b824  38845bf8  addi r4, r4, 0x5bf8
 *   8015b828  4801be0d  bl 0x80177634
 *   8015b82c  80010014  lwz r0, 0x14(r1)
 *   8015b830  7c0803a6  mtlr r0
 *   8015b834  38210010  addi r1, r1, 0x10
 *   8015b838  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5b38092f5a3b8017bb2f4f7e0286d5f9c280b404e30d142a2a6be2ee5a891d2b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80345bf8;

extern int zz_0177634_(int, int);

int f(int p0)
{
    return zz_0177634_(p0, &DAT_80345bf8);
}
