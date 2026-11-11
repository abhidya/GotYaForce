/* MATCHED  gnt4-atan2-bl @ 0x8023cb78  (8 instructions)
 *
 *   8023cb78  9421fff0  stwu r1, -0x10(r1)
 *   8023cb7c  7c0802a6  mflr r0
 *   8023cb80  90010014  stw r0, 0x14(r1)
 *   8023cb84  4bffce01  bl 0x80239984
 *   8023cb88  80010014  lwz r0, 0x14(r1)
 *   8023cb8c  7c0803a6  mtlr r0
 *   8023cb90  38210010  addi r1, r1, 0x10
 *   8023cb94  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 58c1e0d90aad85653af6cc7b9d38f8477ba67f5ef667a98b18b323d308aafb33
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80239984(void);

void f(void)
{
    FUN_80239984();
}
