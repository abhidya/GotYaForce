/* MATCHED  zz_02714b4_ @ 0x802714b4  (8 instructions)
 *
 *   802714b4  9421fff0  stwu r1, -0x10(r1)
 *   802714b8  7c0802a6  mflr r0
 *   802714bc  90010014  stw r0, 0x14(r1)
 *   802714c0  480089a9  bl 0x80279e68
 *   802714c4  80010014  lwz r0, 0x14(r1)
 *   802714c8  7c0803a6  mtlr r0
 *   802714cc  38210010  addi r1, r1, 0x10
 *   802714d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c0f295558cb439dc98d0ee1fc12691cb7acc1db4c4b2e335cdf63c647f69ae6e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279e68_(void);

void f(void)
{
    zz_0279e68_();
}
