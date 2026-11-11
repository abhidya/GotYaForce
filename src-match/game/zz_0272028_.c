/* MATCHED  zz_0272028_ @ 0x80272028  (8 instructions)
 *
 *   80272028  9421fff0  stwu r1, -0x10(r1)
 *   8027202c  7c0802a6  mflr r0
 *   80272030  90010014  stw r0, 0x14(r1)
 *   80272034  4bf8e5d1  bl 0x80200604
 *   80272038  80010014  lwz r0, 0x14(r1)
 *   8027203c  7c0803a6  mtlr r0
 *   80272040  38210010  addi r1, r1, 0x10
 *   80272044  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7da21c1d2ba836e66c8dd3e8155da31da7465cd25a710a3359a4002a55f3eb4d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80200604(void);

void f(void)
{
    FUN_80200604();
}
