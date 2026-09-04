/* MATCHED  zz_00ab6e0_ @ 0x800ab6e0  (8 instructions)
 *
 *   800ab6e0  9421fff0  stwu r1, -0x10(r1)
 *   800ab6e4  7c0802a6  mflr r0
 *   800ab6e8  90010014  stw r0, 0x14(r1)
 *   800ab6ec  4bf6af01  bl 0x800165ec
 *   800ab6f0  80010014  lwz r0, 0x14(r1)
 *   800ab6f4  7c0803a6  mtlr r0
 *   800ab6f8  38210010  addi r1, r1, 0x10
 *   800ab6fc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : edf98a11cb8675e1ac9e80974dc8e7680d70835c1004fdcdeea057bce6428354
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00165ec_(void);

void f(void)
{
    zz_00165ec_();
}
