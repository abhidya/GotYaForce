/* MATCHED  zz_0040e94_ @ 0x80040e94  (8 instructions)
 *
 *   80040e94  9421fff0  stwu r1, -0x10(r1)
 *   80040e98  7c0802a6  mflr r0
 *   80040e9c  90010014  stw r0, 0x14(r1)
 *   80040ea0  4820343d  bl 0x802442dc
 *   80040ea4  80010014  lwz r0, 0x14(r1)
 *   80040ea8  7c0803a6  mtlr r0
 *   80040eac  38210010  addi r1, r1, 0x10
 *   80040eb0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ab4d75fd24e5ba39a4023630ec6a24c7ffc003cea0dbb20811ba15af82c499db
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_802442dc(void);

void f(void)
{
    FUN_802442dc();
}
