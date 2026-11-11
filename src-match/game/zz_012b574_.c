/* MATCHED  zz_012b574_ @ 0x8012b574  (10 instructions)
 *
 *   8012b574  9421fff0  stwu r1, -0x10(r1)
 *   8012b578  7c0802a6  mflr r0
 *   8012b57c  3c808033  lis r4, -0x7fcd
 *   8012b580  90010014  stw r0, 0x14(r1)
 *   8012b584  3884237c  addi r4, r4, 0x237c
 *   8012b588  4804eded  bl 0x8017a374
 *   8012b58c  80010014  lwz r0, 0x14(r1)
 *   8012b590  7c0803a6  mtlr r0
 *   8012b594  38210010  addi r1, r1, 0x10
 *   8012b598  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 880440ae4888f283aa52301718dc2267e8d543e8f2291b6580d4fc356955aad0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8033237c;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_8033237c);
}
