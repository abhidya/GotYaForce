/* MATCHED  zz_0271598_ @ 0x80271598  (8 instructions)
 *
 *   80271598  9421fff0  stwu r1, -0x10(r1)
 *   8027159c  7c0802a6  mflr r0
 *   802715a0  90010014  stw r0, 0x14(r1)
 *   802715a4  48009511  bl 0x8027aab4
 *   802715a8  80010014  lwz r0, 0x14(r1)
 *   802715ac  7c0803a6  mtlr r0
 *   802715b0  38210010  addi r1, r1, 0x10
 *   802715b4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a5d9499349eb3b1169fbce06256d348bcf5de3dc3300dc5db30a1afab03a00ff
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027aab4_(void);

void f(void)
{
    zz_027aab4_();
}
