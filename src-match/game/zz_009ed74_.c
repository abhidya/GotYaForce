/* MATCHED  zz_009ed74_ @ 0x8009ed74  (8 instructions)
 *
 *   8009ed74  9421fff0  stwu r1, -0x10(r1)
 *   8009ed78  7c0802a6  mflr r0
 *   8009ed7c  90010014  stw r0, 0x14(r1)
 *   8009ed80  4bf76f49  bl 0x80015cc8
 *   8009ed84  80010014  lwz r0, 0x14(r1)
 *   8009ed88  7c0803a6  mtlr r0
 *   8009ed8c  38210010  addi r1, r1, 0x10
 *   8009ed90  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : cff525530fc334dba238ddc41af0349f83a2e0a02a7bbfa9e256c7e9417aa296
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0015cc8_(void);

void f(void)
{
    zz_0015cc8_();
}
