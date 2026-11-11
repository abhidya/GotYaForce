/* MATCHED  zz_0008970_ @ 0x80008970  (10 instructions)
 *
 *   80008970  9421fff0  stwu r1, -0x10(r1)
 *   80008974  7c0802a6  mflr r0
 *   80008978  7c641b78  mr r4, r3
 *   8000897c  90010014  stw r0, 0x14(r1)
 *   80008980  806dac70  lwz r3, -0x5390(r13)
 *   80008984  4823e881  bl 0x80247204
 *   80008988  80010014  lwz r0, 0x14(r1)
 *   8000898c  7c0803a6  mtlr r0
 *   80008990  38210010  addi r1, r1, 0x10
 *   80008994  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 119ee65abb5ec2f79d4cabc2f3a4b8aa3abca08b09685b853e6ad0a1ad3fe3d6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436210;

extern int FUN_80247204(int, int);

int f(int p0)
{
    return FUN_80247204(DAT_80436210, p0);
}
