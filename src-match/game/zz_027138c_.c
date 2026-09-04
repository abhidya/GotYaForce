/* MATCHED  zz_027138c_ @ 0x8027138c  (9 instructions)
 *
 *   8027138c  9421fff0  stwu r1, -0x10(r1)
 *   80271390  7c0802a6  mflr r0
 *   80271394  90010014  stw r0, 0x14(r1)
 *   80271398  480080e9  bl 0x80279480
 *   8027139c  80010014  lwz r0, 0x14(r1)
 *   802713a0  38600000  li r3, 0
 *   802713a4  7c0803a6  mtlr r0
 *   802713a8  38210010  addi r1, r1, 0x10
 *   802713ac  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz li mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 69adf37069b0d40dbc9fd0e523bd36dd802b597d51c93d58c172011be3fb1944
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0279480_(void);

int f(void)
{
    zz_0279480_();
    return 0;
}
