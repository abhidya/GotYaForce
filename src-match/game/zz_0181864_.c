/* MATCHED  zz_0181864_ @ 0x80181864  (10 instructions)
 *
 *   80181864  9421fff0  stwu r1, -0x10(r1)
 *   80181868  7c0802a6  mflr r0
 *   8018186c  38600000  li r3, 0
 *   80181870  3880007b  li r4, 0x7b
 *   80181874  90010014  stw r0, 0x14(r1)
 *   80181878  4bf6eaf5  bl 0x800f036c
 *   8018187c  80010014  lwz r0, 0x14(r1)
 *   80181880  7c0803a6  mtlr r0
 *   80181884  38210010  addi r1, r1, 0x10
 *   80181888  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 8784167aeace207c489dd14553cb1c719dd12bae96f8f09b1598e024d55fa1a3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00f036c_(int, int);

void f(void)
{
    zz_00f036c_(0, 0x7b);
}
