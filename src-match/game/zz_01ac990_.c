/* MATCHED  zz_01ac990_ @ 0x801ac990  (8 instructions)
 *
 *   801ac990  9421fff0  stwu r1, -0x10(r1)
 *   801ac994  7c0802a6  mflr r0
 *   801ac998  90010014  stw r0, 0x14(r1)
 *   801ac99c  4bffae4d  bl 0x801a77e8
 *   801ac9a0  80010014  lwz r0, 0x14(r1)
 *   801ac9a4  7c0803a6  mtlr r0
 *   801ac9a8  38210010  addi r1, r1, 0x10
 *   801ac9ac  4e800020  blr
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
