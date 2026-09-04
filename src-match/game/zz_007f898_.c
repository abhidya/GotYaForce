/* MATCHED  zz_007f898_ @ 0x8007f898  (8 instructions)
 *
 *   8007f898  9421fff0  stwu r1, -0x10(r1)
 *   8007f89c  7c0802a6  mflr r0
 *   8007f8a0  90010014  stw r0, 0x14(r1)
 *   8007f8a4  480095ad  bl 0x80088e50
 *   8007f8a8  80010014  lwz r0, 0x14(r1)
 *   8007f8ac  7c0803a6  mtlr r0
 *   8007f8b0  38210010  addi r1, r1, 0x10
 *   8007f8b4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7e6aa516b554e1606c7615026a1a39d1574b61b45204f6a94caf5619fab30426
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0088e50_(void);

void f(void)
{
    zz_0088e50_();
}
