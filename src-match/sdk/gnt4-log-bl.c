/* MATCHED  gnt4-log-bl @ 0x8023cbd8  (8 instructions)
 *
 *   8023cbd8  9421fff0  stwu r1, -0x10(r1)
 *   8023cbdc  7c0802a6  mflr r0
 *   8023cbe0  90010014  stw r0, 0x14(r1)
 *   8023cbe4  4bffd591  bl 0x8023a174
 *   8023cbe8  80010014  lwz r0, 0x14(r1)
 *   8023cbec  7c0803a6  mtlr r0
 *   8023cbf0  38210010  addi r1, r1, 0x10
 *   8023cbf4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : fd0f0a54a8ffe96cffa2b0879d17b17852f248b4b682328c36913cc2f9b0de69
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8023a174(void);

void f(void)
{
    FUN_8023a174();
}
