/* MATCHED  zz_00efda8_ @ 0x800efda8  (8 instructions)
 *
 *   800efda8  9421fff0  stwu r1, -0x10(r1)
 *   800efdac  7c0802a6  mflr r0
 *   800efdb0  90010014  stw r0, 0x14(r1)
 *   800efdb4  4bffd2a5  bl 0x800ed058
 *   800efdb8  80010014  lwz r0, 0x14(r1)
 *   800efdbc  7c0803a6  mtlr r0
 *   800efdc0  38210010  addi r1, r1, 0x10
 *   800efdc4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7d14ba19847c37f9c26b9c8bf52fbfe4179d2abfeced18dc577c20a44ea65c96
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00ed058_(void);

void f(void)
{
    zz_00ed058_();
}
