/* MATCHED  zz_015ad84_ @ 0x8015ad84  (10 instructions)
 *
 *   8015ad84  9421fff0  stwu r1, -0x10(r1)
 *   8015ad88  7c0802a6  mflr r0
 *   8015ad8c  3c808034  lis r4, -0x7fcc
 *   8015ad90  90010014  stw r0, 0x14(r1)
 *   8015ad94  38844884  addi r4, r4, 0x4884
 *   8015ad98  4801f5dd  bl 0x8017a374
 *   8015ad9c  80010014  lwz r0, 0x14(r1)
 *   8015ada0  7c0803a6  mtlr r0
 *   8015ada4  38210010  addi r1, r1, 0x10
 *   8015ada8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0d7b65d91159377f0937efb408074f79799a49380ebd092c236c2f199a3b9147
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80344884;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_80344884);
}
