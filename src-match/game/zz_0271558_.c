/* MATCHED  zz_0271558_ @ 0x80271558  (8 instructions)
 *
 *   80271558  9421fff0  stwu r1, -0x10(r1)
 *   8027155c  7c0802a6  mflr r0
 *   80271560  90010014  stw r0, 0x14(r1)
 *   80271564  48008dd1  bl 0x8027a334
 *   80271568  80010014  lwz r0, 0x14(r1)
 *   8027156c  7c0803a6  mtlr r0
 *   80271570  38210010  addi r1, r1, 0x10
 *   80271574  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 12faffe573ed9d95422d4249fc3e06e58ef91ecb5c14ffd578ce8f9db5714d5a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027a334_(void);

void f(void)
{
    zz_027a334_();
}
