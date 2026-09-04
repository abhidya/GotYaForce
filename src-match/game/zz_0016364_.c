/* MATCHED  zz_0016364_ @ 0x80016364  (8 instructions)
 *
 *   80016364  9421fff0  stwu r1, -0x10(r1)
 *   80016368  7c0802a6  mflr r0
 *   8001636c  90010014  stw r0, 0x14(r1)
 *   80016370  48000015  bl 0x80016384
 *   80016374  80010014  lwz r0, 0x14(r1)
 *   80016378  7c0803a6  mtlr r0
 *   8001637c  38210010  addi r1, r1, 0x10
 *   80016380  4e800020  blr
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
