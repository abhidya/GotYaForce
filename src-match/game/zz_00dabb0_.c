/* MATCHED  zz_00dabb0_ @ 0x800dabb0  (10 instructions)
 *
 *   800dabb0  9421fff0  stwu r1, -0x10(r1)
 *   800dabb4  7c0802a6  mflr r0
 *   800dabb8  3c808031  lis r4, -0x7fcf
 *   800dabbc  90010014  stw r0, 0x14(r1)
 *   800dabc0  38841c54  addi r4, r4, 0x1c54
 *   800dabc4  4801726d  bl 0x800f1e30
 *   800dabc8  80010014  lwz r0, 0x14(r1)
 *   800dabcc  7c0803a6  mtlr r0
 *   800dabd0  38210010  addi r1, r1, 0x10
 *   800dabd4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a3deb4f8d97395ac2b9539d43d575e663fef60b65d6693ed4c45c9a645031783
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80311c54;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_80311c54);
}
