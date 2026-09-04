/* MATCHED  zz_02ab418_ @ 0x802ab418  (8 instructions)
 *
 *   802ab418  9421fff0  stwu r1, -0x10(r1)
 *   802ab41c  7c0802a6  mflr r0
 *   802ab420  90010014  stw r0, 0x14(r1)
 *   802ab424  4bfd0131  bl 0x8027b554
 *   802ab428  80010014  lwz r0, 0x14(r1)
 *   802ab42c  7c0803a6  mtlr r0
 *   802ab430  38210010  addi r1, r1, 0x10
 *   802ab434  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d3d9d66a8cde87a0927cf11b98fc1b5b5af87563824ce777c12e5abcc14aa7c3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027b554_(void);

void f(void)
{
    zz_027b554_();
}
