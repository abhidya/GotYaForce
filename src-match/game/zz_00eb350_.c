/* MATCHED  zz_00eb350_ @ 0x800eb350  (10 instructions)
 *
 *   800eb350  9421fff0  stwu r1, -0x10(r1)
 *   800eb354  7c0802a6  mflr r0
 *   800eb358  3c808032  lis r4, -0x7fce
 *   800eb35c  90010014  stw r0, 0x14(r1)
 *   800eb360  3884b148  addi r4, r4, -0x4eb8
 *   800eb364  48013a09  bl 0x800fed6c
 *   800eb368  80010014  lwz r0, 0x14(r1)
 *   800eb36c  7c0803a6  mtlr r0
 *   800eb370  38210010  addi r1, r1, 0x10
 *   800eb374  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d55853b2335c9dda2a693e22d7120d48e7e448fc8eb93e35ab0b6439bd59cf29
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8031b148;

extern int zz_00fed6c_(int, int);

int f(int p0)
{
    return zz_00fed6c_(p0, &DAT_8031b148);
}
