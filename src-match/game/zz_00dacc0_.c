/* MATCHED  zz_00dacc0_ @ 0x800dacc0  (10 instructions)
 *
 *   800dacc0  9421fff0  stwu r1, -0x10(r1)
 *   800dacc4  7c0802a6  mflr r0
 *   800dacc8  3c808031  lis r4, -0x7fcf
 *   800daccc  90010014  stw r0, 0x14(r1)
 *   800dacd0  38841c68  addi r4, r4, 0x1c68
 *   800dacd4  4801715d  bl 0x800f1e30
 *   800dacd8  80010014  lwz r0, 0x14(r1)
 *   800dacdc  7c0803a6  mtlr r0
 *   800dace0  38210010  addi r1, r1, 0x10
 *   800dace4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : f7ca64e514cecf915c3e58ab8e9819520cbf5e6912adc69e5c8775fda97c8368
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80311c68;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_80311c68);
}
