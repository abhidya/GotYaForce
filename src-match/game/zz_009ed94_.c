/* MATCHED  zz_009ed94_ @ 0x8009ed94  (8 instructions)
 *
 *   8009ed94  9421fff0  stwu r1, -0x10(r1)
 *   8009ed98  7c0802a6  mflr r0
 *   8009ed9c  90010014  stw r0, 0x14(r1)
 *   8009eda0  4bf775e5  bl 0x80016384
 *   8009eda4  80010014  lwz r0, 0x14(r1)
 *   8009eda8  7c0803a6  mtlr r0
 *   8009edac  38210010  addi r1, r1, 0x10
 *   8009edb0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0ef8e19ca1440383e6abd51027c979a018d648761af3f19fc70ca82dc3d74507
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0016384_(void);

void f(void)
{
    zz_0016384_();
}
