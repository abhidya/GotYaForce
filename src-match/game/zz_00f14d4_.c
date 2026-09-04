/* MATCHED  zz_00f14d4_ @ 0x800f14d4  (11 instructions)
 *
 *   800f14d4  9421fff0  stwu r1, -0x10(r1)
 *   800f14d8  7c0802a6  mflr r0
 *   800f14dc  38600000  li r3, 0
 *   800f14e0  38800010  li r4, 0x10
 *   800f14e4  90010014  stw r0, 0x14(r1)
 *   800f14e8  38a00000  li r5, 0
 *   800f14ec  4bffc2e9  bl 0x800ed7d4
 *   800f14f0  80010014  lwz r0, 0x14(r1)
 *   800f14f4  7c0803a6  mtlr r0
 *   800f14f8  38210010  addi r1, r1, 0x10
 *   800f14fc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : bd5b8bfb5e8140e37d56cff14124e6a075e883ad4d00aece8fb398336a8a001a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00ed7d4_(int, int, int);

void f(void)
{
    zz_00ed7d4_(0, 0x10, 0);
}
