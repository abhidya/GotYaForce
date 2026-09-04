/* MATCHED  zz_02aa650_ @ 0x802aa650  (8 instructions)
 *
 *   802aa650  9421fff0  stwu r1, -0x10(r1)
 *   802aa654  7c0802a6  mflr r0
 *   802aa658  90010014  stw r0, 0x14(r1)
 *   802aa65c  4bfce0f9  bl 0x80278754
 *   802aa660  80010014  lwz r0, 0x14(r1)
 *   802aa664  7c0803a6  mtlr r0
 *   802aa668  38210010  addi r1, r1, 0x10
 *   802aa66c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3442becdff9d2246f2363705bcddfae7fecd7d7fbe00038363e655648be94df3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0278754_(void);

void f(void)
{
    zz_0278754_();
}
