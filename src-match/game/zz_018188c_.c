/* MATCHED  zz_018188c_ @ 0x8018188c  (10 instructions)
 *
 *   8018188c  9421fff0  stwu r1, -0x10(r1)
 *   80181890  7c0802a6  mflr r0
 *   80181894  38600000  li r3, 0
 *   80181898  3880007d  li r4, 0x7d
 *   8018189c  90010014  stw r0, 0x14(r1)
 *   801818a0  4bf6eacd  bl 0x800f036c
 *   801818a4  80010014  lwz r0, 0x14(r1)
 *   801818a8  7c0803a6  mtlr r0
 *   801818ac  38210010  addi r1, r1, 0x10
 *   801818b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 8818ad70385ad8cdab25bd55c873d9d094b5ed85fb56b0a1cb19994dd982e219
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00f036c_(int, int);

void f(void)
{
    zz_00f036c_(0, 0x7d);
}
