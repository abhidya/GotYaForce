/* MATCHED  gnt4-exp-bl @ 0x8023cb98  (8 instructions)
 *
 *   8023cb98  9421fff0  stwu r1, -0x10(r1)
 *   8023cb9c  7c0802a6  mflr r0
 *   8023cba0  90010014  stw r0, 0x14(r1)
 *   8023cba4  4bffd071  bl 0x80239c14
 *   8023cba8  80010014  lwz r0, 0x14(r1)
 *   8023cbac  7c0803a6  mtlr r0
 *   8023cbb0  38210010  addi r1, r1, 0x10
 *   8023cbb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2ef1ca7c2bacced96d4dbbd5fc7293425f62b37768d929dc5b6fdfb646935802
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80239c14(void);

void f(void)
{
    FUN_80239c14();
}
