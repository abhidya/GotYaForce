/* MATCHED  zz_018ed80_ @ 0x8018ed80  (10 instructions)
 *
 *   8018ed80  9421fff0  stwu r1, -0x10(r1)
 *   8018ed84  7c0802a6  mflr r0
 *   8018ed88  3c808036  lis r4, -0x7fca
 *   8018ed8c  90010014  stw r0, 0x14(r1)
 *   8018ed90  38845854  addi r4, r4, 0x5854
 *   8018ed94  4bfeaa81  bl 0x80179814
 *   8018ed98  80010014  lwz r0, 0x14(r1)
 *   8018ed9c  7c0803a6  mtlr r0
 *   8018eda0  38210010  addi r1, r1, 0x10
 *   8018eda4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6189c82678110e2edc1bc274f7b0a740b3d6567f1d7c6945dfa4df78a2654a08
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80365854;

extern int zz_0179814_(int, int);

int f(int p0)
{
    return zz_0179814_(p0, &DAT_80365854);
}
