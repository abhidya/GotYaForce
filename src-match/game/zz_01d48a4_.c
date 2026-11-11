/* MATCHED  zz_01d48a4_ @ 0x801d48a4  (10 instructions)
 *
 *   801d48a4  9421fff0  stwu r1, -0x10(r1)
 *   801d48a8  7c0802a6  mflr r0
 *   801d48ac  3c808039  lis r4, -0x7fc7
 *   801d48b0  90010014  stw r0, 0x14(r1)
 *   801d48b4  3884bdfc  addi r4, r4, -0x4204
 *   801d48b8  4bf1d579  bl 0x800f1e30
 *   801d48bc  80010014  lwz r0, 0x14(r1)
 *   801d48c0  7c0803a6  mtlr r0
 *   801d48c4  38210010  addi r1, r1, 0x10
 *   801d48c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : f72072dfb799b7c2e40a658d9b82690a1db80566408f3f89fe7ae498bbbef01b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8038bdfc;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_8038bdfc);
}
