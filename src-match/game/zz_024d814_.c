/* MATCHED  zz_024d814_ @ 0x8024d814  (9 instructions)
 *
 *   8024d814  9421fff0  stwu r1, -0x10(r1)
 *   8024d818  7c0802a6  mflr r0
 *   8024d81c  388007ff  li r4, 0x7ff
 *   8024d820  90010014  stw r0, 0x14(r1)
 *   8024d824  4bfffd4d  bl 0x8024d570
 *   8024d828  80010014  lwz r0, 0x14(r1)
 *   8024d82c  7c0803a6  mtlr r0
 *   8024d830  38210010  addi r1, r1, 0x10
 *   8024d834  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 97eb5c6c5748cabba3c1d43692ce57921c3638ca9baf815d8ebfdd7498c0943c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_024d570_(int, int);

void f(int p0)
{
    zz_024d570_(p0, 0x7ff);
}
