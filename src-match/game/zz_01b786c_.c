/* MATCHED  zz_01b786c_ @ 0x801b786c  (10 instructions)
 *
 *   801b786c  9421fff0  stwu r1, -0x10(r1)
 *   801b7870  7c0802a6  mflr r0
 *   801b7874  7c641b78  mr r4, r3
 *   801b7878  38600000  li r3, 0
 *   801b787c  90010014  stw r0, 0x14(r1)
 *   801b7880  4bffff79  bl 0x801b77f8
 *   801b7884  80010014  lwz r0, 0x14(r1)
 *   801b7888  7c0803a6  mtlr r0
 *   801b788c  38210010  addi r1, r1, 0x10
 *   801b7890  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 973eff3e577a34b94839273f591e9979b5536a3d5f54826d54e2822882283ef6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01b77f8_(int, int);

void f(int p0)
{
    zz_01b77f8_(0, p0);
}
