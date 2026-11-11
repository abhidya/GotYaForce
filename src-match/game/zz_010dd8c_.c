/* MATCHED  zz_010dd8c_ @ 0x8010dd8c  (10 instructions)
 *
 *   8010dd8c  9421fff0  stwu r1, -0x10(r1)
 *   8010dd90  7c0802a6  mflr r0
 *   8010dd94  3c60803d  lis r3, -0x7fc3
 *   8010dd98  90010014  stw r0, 0x14(r1)
 *   8010dd9c  386342a0  addi r3, r3, 0x42a0
 *   8010dda0  4bffff35  bl 0x8010dcd4
 *   8010dda4  80010014  lwz r0, 0x14(r1)
 *   8010dda8  7c0803a6  mtlr r0
 *   8010ddac  38210010  addi r1, r1, 0x10
 *   8010ddb0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a2d269e3eb4c1b6140c3ca7324fcf93db2f49e2ef92fe4eeed6dab31d76a0638
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803d42a0;

extern int zz_010dcd4_(int);

int f(void)
{
    return zz_010dcd4_(&DAT_803d42a0);
}
