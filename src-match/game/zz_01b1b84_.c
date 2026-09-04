/* MATCHED  zz_01b1b84_ @ 0x801b1b84  (8 instructions)
 *
 *   801b1b84  9421fff0  stwu r1, -0x10(r1)
 *   801b1b88  7c0802a6  mflr r0
 *   801b1b8c  90010014  stw r0, 0x14(r1)
 *   801b1b90  4bfff485  bl 0x801b1014
 *   801b1b94  80010014  lwz r0, 0x14(r1)
 *   801b1b98  7c0803a6  mtlr r0
 *   801b1b9c  38210010  addi r1, r1, 0x10
 *   801b1ba0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 8ebe75fe413255039a4d81f200ff0da0c794e480ee84d9bb83b33499cf68604d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01b1014_(void);

void f(void)
{
    zz_01b1014_();
}
