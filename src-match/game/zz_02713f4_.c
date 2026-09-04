/* MATCHED  zz_02713f4_ @ 0x802713f4  (8 instructions)
 *
 *   802713f4  9421fff0  stwu r1, -0x10(r1)
 *   802713f8  7c0802a6  mflr r0
 *   802713fc  90010014  stw r0, 0x14(r1)
 *   80271400  48008099  bl 0x80279498
 *   80271404  80010014  lwz r0, 0x14(r1)
 *   80271408  7c0803a6  mtlr r0
 *   8027140c  38210010  addi r1, r1, 0x10
 *   80271410  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ce6f5c867da9bd3b96ae945b1bf125feef1bdc16768bbcf7e63212a2fd90b0ff
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279498_(void);

void f(void)
{
    zz_0279498_();
}
