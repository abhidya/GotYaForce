/* MATCHED  zz_0270b88_ @ 0x80270b88  (12 instructions)
 *
 *   80270b88  9421fff0  stwu r1, -0x10(r1)
 *   80270b8c  7c0802a6  mflr r0
 *   80270b90  3c608040  lis r3, -0x7fc0
 *   80270b94  38800000  li r4, 0
 *   80270b98  90010014  stw r0, 0x14(r1)
 *   80270b9c  386302b4  addi r3, r3, 0x2b4
 *   80270ba0  38a003c0  li r5, 0x3c0
 *   80270ba4  4bd94869  bl 0x8000540c
 *   80270ba8  80010014  lwz r0, 0x14(r1)
 *   80270bac  7c0803a6  mtlr r0
 *   80270bb0  38210010  addi r1, r1, 0x10
 *   80270bb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1bb09c90035d9a7bc882586e9301647f409ed846ebfd4f17374db5f3680392c7
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_804002b4;

extern int FUN_8000540c(int, int, int);

int f(void)
{
    return FUN_8000540c(&DAT_804002b4, 0, 0x3c0);
}
