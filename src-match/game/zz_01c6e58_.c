/* MATCHED  zz_01c6e58_ @ 0x801c6e58  (10 instructions)
 *
 *   801c6e58  9421fff0  stwu r1, -0x10(r1)
 *   801c6e5c  7c0802a6  mflr r0
 *   801c6e60  38600000  li r3, 0
 *   801c6e64  3880007b  li r4, 0x7b
 *   801c6e68  90010014  stw r0, 0x14(r1)
 *   801c6e6c  4bf29501  bl 0x800f036c
 *   801c6e70  80010014  lwz r0, 0x14(r1)
 *   801c6e74  7c0803a6  mtlr r0
 *   801c6e78  38210010  addi r1, r1, 0x10
 *   801c6e7c  4e800020  blr
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
