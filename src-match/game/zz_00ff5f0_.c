/* MATCHED  zz_00ff5f0_ @ 0x800ff5f0  (10 instructions)
 *
 *   800ff5f0  9421fff0  stwu r1, -0x10(r1)
 *   800ff5f4  7c0802a6  mflr r0
 *   800ff5f8  90010014  stw r0, 0x14(r1)
 *   800ff5fc  806d8394  lwz r3, -0x7c6c(r13)
 *   800ff600  38631838  addi r3, r3, 0x1838
 *   800ff604  480d0b6d  bl 0x801d0170
 *   800ff608  80010014  lwz r0, 0x14(r1)
 *   800ff60c  7c0803a6  mtlr r0
 *   800ff610  38210010  addi r1, r1, 0x10
 *   800ff614  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 37c0852947c2854c2367fb3465a0f5c61a0ec85a73b0572bcfe1f40054080f4e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int PTR_DAT_80433934;

extern int zz_01d0170_(int);

int f(void)
{
    return zz_01d0170_(PTR_DAT_80433934 + 0x1838);
}
