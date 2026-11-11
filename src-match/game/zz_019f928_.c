/* MATCHED  zz_019f928_ @ 0x8019f928  (10 instructions)
 *
 *   8019f928  9421fff0  stwu r1, -0x10(r1)
 *   8019f92c  7c0802a6  mflr r0
 *   8019f930  3c808037  lis r4, -0x7fc9
 *   8019f934  90010014  stw r0, 0x14(r1)
 *   8019f938  388464b4  addi r4, r4, 0x64b4
 *   8019f93c  4bf5f431  bl 0x800fed6c
 *   8019f940  80010014  lwz r0, 0x14(r1)
 *   8019f944  7c0803a6  mtlr r0
 *   8019f948  38210010  addi r1, r1, 0x10
 *   8019f94c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b2fbc895122c7decbf7b3db7a28a6ca87132233fc932b60e668d7219573768c5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803764b4;

extern int zz_00fed6c_(int, int);

int f(int p0)
{
    return zz_00fed6c_(p0, &DAT_803764b4);
}
