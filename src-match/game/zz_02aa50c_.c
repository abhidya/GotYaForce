/* MATCHED  zz_02aa50c_ @ 0x802aa50c  (9 instructions)
 *
 *   802aa50c  9421fff0  stwu r1, -0x10(r1)
 *   802aa510  7c0802a6  mflr r0
 *   802aa514  38600006  li r3, 6
 *   802aa518  90010014  stw r0, 0x14(r1)
 *   802aa51c  4bfcdab9  bl 0x80277fd4
 *   802aa520  80010014  lwz r0, 0x14(r1)
 *   802aa524  7c0803a6  mtlr r0
 *   802aa528  38210010  addi r1, r1, 0x10
 *   802aa52c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : dd4f5e6c9ede91db5425a2f1a72ac896519be0f1b3396a9aea91b4691783168e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0277fd4_(int);

void f(void)
{
    zz_0277fd4_(6);
}
