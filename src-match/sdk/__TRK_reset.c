/* MATCHED  __TRK_reset @ 0x800053e0  (11 instructions)
 *
 *   800053e0  9421fff0  stwu r1, -0x10(r1)
 *   800053e4  7c0802a6  mflr r0
 *   800053e8  38600000  li r3, 0
 *   800053ec  38800000  li r4, 0
 *   800053f0  90010014  stw r0, 0x14(r1)
 *   800053f4  38a00000  li r5, 0
 *   800053f8  481ff4c1  bl 0x802048b8
 *   800053fc  80010014  lwz r0, 0x14(r1)
 *   80005400  7c0803a6  mtlr r0
 *   80005404  38210010  addi r1, r1, 0x10
 *   80005408  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 250df5d682383c1af649c92f76422071826226c53e6ae7b55eab79a142a87ff0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02048b8_(int, int, int);

void f(void)
{
    zz_02048b8_(0, 0, 0);
}
