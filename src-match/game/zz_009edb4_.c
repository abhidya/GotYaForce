/* MATCHED  zz_009edb4_ @ 0x8009edb4  (8 instructions)
 *
 *   8009edb4  9421fff0  stwu r1, -0x10(r1)
 *   8009edb8  7c0802a6  mflr r0
 *   8009edbc  90010014  stw r0, 0x14(r1)
 *   8009edc0  4bf7782d  bl 0x800165ec
 *   8009edc4  80010014  lwz r0, 0x14(r1)
 *   8009edc8  7c0803a6  mtlr r0
 *   8009edcc  38210010  addi r1, r1, 0x10
 *   8009edd0  4e800020  blr
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
