/* MATCHED  zz_00f0f64_ @ 0x800f0f64  (8 instructions)
 *
 *   800f0f64  9421fff0  stwu r1, -0x10(r1)
 *   800f0f68  7c0802a6  mflr r0
 *   800f0f6c  90010014  stw r0, 0x14(r1)
 *   800f0f70  4bffc671  bl 0x800ed5e0
 *   800f0f74  80010014  lwz r0, 0x14(r1)
 *   800f0f78  7c0803a6  mtlr r0
 *   800f0f7c  38210010  addi r1, r1, 0x10
 *   800f0f80  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a03f7109fb905e435828745adf5512146d98427dc471b2607fb84d9fe1380989
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00ed5e0_(void);

void f(void)
{
    zz_00ed5e0_();
}
