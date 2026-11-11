/* MATCHED  zz_01d4ac0_ @ 0x801d4ac0  (10 instructions)
 *
 *   801d4ac0  9421fff0  stwu r1, -0x10(r1)
 *   801d4ac4  7c0802a6  mflr r0
 *   801d4ac8  3c808039  lis r4, -0x7fc7
 *   801d4acc  90010014  stw r0, 0x14(r1)
 *   801d4ad0  3884be24  addi r4, r4, -0x41dc
 *   801d4ad4  4bf1d35d  bl 0x800f1e30
 *   801d4ad8  80010014  lwz r0, 0x14(r1)
 *   801d4adc  7c0803a6  mtlr r0
 *   801d4ae0  38210010  addi r1, r1, 0x10
 *   801d4ae4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6be8d93f71d7534ecf12f41096a9ec1d855970b7b484782c65db8b51074b3f00
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8038be24;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_8038be24);
}
