/* MATCHED  zz_018cb48_ @ 0x8018cb48  (8 instructions)
 *
 *   8018cb48  9421fff0  stwu r1, -0x10(r1)
 *   8018cb4c  7c0802a6  mflr r0
 *   8018cb50  90010014  stw r0, 0x14(r1)
 *   8018cb54  48000015  bl 0x8018cb68
 *   8018cb58  80010014  lwz r0, 0x14(r1)
 *   8018cb5c  7c0803a6  mtlr r0
 *   8018cb60  38210010  addi r1, r1, 0x10
 *   8018cb64  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0d269c02c1b36cdf34b6291213f5e478f41adaf028331b13557e1a61d87fbec9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_018cb68_(void);

void f(void)
{
    zz_018cb68_();
}
