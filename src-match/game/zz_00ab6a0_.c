/* MATCHED  zz_00ab6a0_ @ 0x800ab6a0  (8 instructions)
 *
 *   800ab6a0  9421fff0  stwu r1, -0x10(r1)
 *   800ab6a4  7c0802a6  mflr r0
 *   800ab6a8  90010014  stw r0, 0x14(r1)
 *   800ab6ac  4bf6a61d  bl 0x80015cc8
 *   800ab6b0  80010014  lwz r0, 0x14(r1)
 *   800ab6b4  7c0803a6  mtlr r0
 *   800ab6b8  38210010  addi r1, r1, 0x10
 *   800ab6bc  4e800020  blr
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
