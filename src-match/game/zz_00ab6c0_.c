/* MATCHED  zz_00ab6c0_ @ 0x800ab6c0  (8 instructions)
 *
 *   800ab6c0  9421fff0  stwu r1, -0x10(r1)
 *   800ab6c4  7c0802a6  mflr r0
 *   800ab6c8  90010014  stw r0, 0x14(r1)
 *   800ab6cc  4bf6acb9  bl 0x80016384
 *   800ab6d0  80010014  lwz r0, 0x14(r1)
 *   800ab6d4  7c0803a6  mtlr r0
 *   800ab6d8  38210010  addi r1, r1, 0x10
 *   800ab6dc  4e800020  blr
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
