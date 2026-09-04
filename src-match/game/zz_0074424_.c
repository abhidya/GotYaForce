/* MATCHED  zz_0074424_ @ 0x80074424  (9 instructions)
 *
 *   80074424  9421fff0  stwu r1, -0x10(r1)
 *   80074428  7c0802a6  mflr r0
 *   8007442c  38800000  li r4, 0
 *   80074430  90010014  stw r0, 0x14(r1)
 *   80074434  480e3c69  bl 0x8015809c
 *   80074438  80010014  lwz r0, 0x14(r1)
 *   8007443c  7c0803a6  mtlr r0
 *   80074440  38210010  addi r1, r1, 0x10
 *   80074444  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5033d1d8c601b1c4d86cc4b3dea2d88d88e1331bb2771b0dcea4563d4e218cb8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_015809c_(int, int);

void f(int p0)
{
    zz_015809c_(p0, 0);
}
