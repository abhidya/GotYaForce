/* MATCHED  zz_01ac224_ @ 0x801ac224  (8 instructions)
 *
 *   801ac224  9421fff0  stwu r1, -0x10(r1)
 *   801ac228  7c0802a6  mflr r0
 *   801ac22c  90010014  stw r0, 0x14(r1)
 *   801ac230  4bffb5b9  bl 0x801a77e8
 *   801ac234  80010014  lwz r0, 0x14(r1)
 *   801ac238  7c0803a6  mtlr r0
 *   801ac23c  38210010  addi r1, r1, 0x10
 *   801ac240  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b6752261b38c18a7abe2a5d3705323fde890c57c17bb33e1d992858b8f829e03
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01a77e8_(void);

void f(void)
{
    zz_01a77e8_();
}
