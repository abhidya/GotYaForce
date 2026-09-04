/* MATCHED  zz_027136c_ @ 0x8027136c  (8 instructions)
 *
 *   8027136c  9421fff0  stwu r1, -0x10(r1)
 *   80271370  7c0802a6  mflr r0
 *   80271374  90010014  stw r0, 0x14(r1)
 *   80271378  480080f1  bl 0x80279468
 *   8027137c  80010014  lwz r0, 0x14(r1)
 *   80271380  7c0803a6  mtlr r0
 *   80271384  38210010  addi r1, r1, 0x10
 *   80271388  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 02dc7c78e63b736e7c2619700da9e9ec9d8e164eb442305dd348f49f3d6f196a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279468_(void);

void f(void)
{
    zz_0279468_();
}
