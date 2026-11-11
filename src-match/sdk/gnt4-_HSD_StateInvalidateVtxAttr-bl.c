/* MATCHED  gnt4-_HSD_StateInvalidateVtxAttr-bl @ 0x802417e4  (8 instructions)
 *
 *   802417e4  9421fff0  stwu r1, -0x10(r1)
 *   802417e8  7c0802a6  mflr r0
 *   802417ec  90010014  stw r0, 0x14(r1)
 *   802417f0  48009491  bl 0x8024ac80
 *   802417f4  80010014  lwz r0, 0x14(r1)
 *   802417f8  7c0803a6  mtlr r0
 *   802417fc  38210010  addi r1, r1, 0x10
 *   80241800  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9bf0e305a361f8120075169db34bd997325049f307018dfc057e25fff1972f11
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8024ac80(void);

void f(void)
{
    FUN_8024ac80();
}
