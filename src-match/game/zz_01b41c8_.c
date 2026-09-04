/* MATCHED  zz_01b41c8_ @ 0x801b41c8  (8 instructions)
 *
 *   801b41c8  9421fff0  stwu r1, -0x10(r1)
 *   801b41cc  7c0802a6  mflr r0
 *   801b41d0  90010014  stw r0, 0x14(r1)
 *   801b41d4  4bfffdc1  bl 0x801b3f94
 *   801b41d8  80010014  lwz r0, 0x14(r1)
 *   801b41dc  7c0803a6  mtlr r0
 *   801b41e0  38210010  addi r1, r1, 0x10
 *   801b41e4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2af8d30b2a5e21d84c9a49bcdcc70b9c2f9415b49eec15272615ffa81b9f57bc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01b3f94_(void);

void f(void)
{
    zz_01b3f94_();
}
