/* MATCHED  zz_0271494_ @ 0x80271494  (8 instructions)
 *
 *   80271494  9421fff0  stwu r1, -0x10(r1)
 *   80271498  7c0802a6  mflr r0
 *   8027149c  90010014  stw r0, 0x14(r1)
 *   802714a0  48008971  bl 0x80279e10
 *   802714a4  80010014  lwz r0, 0x14(r1)
 *   802714a8  7c0803a6  mtlr r0
 *   802714ac  38210010  addi r1, r1, 0x10
 *   802714b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a0d868da1a887513db2090a6ab7a78cea4083fa325b55fb04dad87c0687e480f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279e10_(void);

void f(void)
{
    zz_0279e10_();
}
