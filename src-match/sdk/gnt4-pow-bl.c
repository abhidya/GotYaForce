/* MATCHED  gnt4-pow-bl @ 0x8023cbf8  (8 instructions)
 *
 *   8023cbf8  9421fff0  stwu r1, -0x10(r1)
 *   8023cbfc  7c0802a6  mflr r0
 *   8023cc00  90010014  stw r0, 0x14(r1)
 *   8023cc04  4bffd7ed  bl 0x8023a3f0
 *   8023cc08  80010014  lwz r0, 0x14(r1)
 *   8023cc0c  7c0803a6  mtlr r0
 *   8023cc10  38210010  addi r1, r1, 0x10
 *   8023cc14  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6caace9418cc38ad6c00bc0d2ab2cbb4c2aef4f8b3df95439321d4816a7dedb2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8023a3f0(void);

void f(void)
{
    FUN_8023a3f0();
}
