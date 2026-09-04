/* MATCHED  zz_0275b78_ @ 0x80275b78  (8 instructions)
 *
 *   80275b78  9421fff0  stwu r1, -0x10(r1)
 *   80275b7c  7c0802a6  mflr r0
 *   80275b80  90010014  stw r0, 0x14(r1)
 *   80275b84  48000c3d  bl 0x802767c0
 *   80275b88  80010014  lwz r0, 0x14(r1)
 *   80275b8c  7c0803a6  mtlr r0
 *   80275b90  38210010  addi r1, r1, 0x10
 *   80275b94  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 20559006bfa92c1ee39d8460c670d4139efefbbdf9e0510510d033bc9c251b71
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02767c0_(void);

void f(void)
{
    zz_02767c0_();
}
