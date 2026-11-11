/* MATCHED  zz_00eb328_ @ 0x800eb328  (10 instructions)
 *
 *   800eb328  9421fff0  stwu r1, -0x10(r1)
 *   800eb32c  7c0802a6  mflr r0
 *   800eb330  3c808032  lis r4, -0x7fce
 *   800eb334  90010014  stw r0, 0x14(r1)
 *   800eb338  3884b130  addi r4, r4, -0x4ed0
 *   800eb33c  48013a31  bl 0x800fed6c
 *   800eb340  80010014  lwz r0, 0x14(r1)
 *   800eb344  7c0803a6  mtlr r0
 *   800eb348  38210010  addi r1, r1, 0x10
 *   800eb34c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 43c85d8f9afdb4e1ad143efb204f5e1f019fd36f982da81c84e7810f4275771a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8031b130;

extern int zz_00fed6c_(int, int);

int f(int p0)
{
    return zz_00fed6c_(p0, &DAT_8031b130);
}
