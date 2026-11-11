/* MATCHED  zz_01d49b0_ @ 0x801d49b0  (10 instructions)
 *
 *   801d49b0  9421fff0  stwu r1, -0x10(r1)
 *   801d49b4  7c0802a6  mflr r0
 *   801d49b8  3c808039  lis r4, -0x7fc7
 *   801d49bc  90010014  stw r0, 0x14(r1)
 *   801d49c0  3884be10  addi r4, r4, -0x41f0
 *   801d49c4  4bf1d46d  bl 0x800f1e30
 *   801d49c8  80010014  lwz r0, 0x14(r1)
 *   801d49cc  7c0803a6  mtlr r0
 *   801d49d0  38210010  addi r1, r1, 0x10
 *   801d49d4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 828489a649f855ccc16b7f18b4a603977d30161ce253e2ff0a686d993518cf07
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8038be10;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_8038be10);
}
