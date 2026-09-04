/* MATCHED  zz_01c6e30_ @ 0x801c6e30  (10 instructions)
 *
 *   801c6e30  9421fff0  stwu r1, -0x10(r1)
 *   801c6e34  7c0802a6  mflr r0
 *   801c6e38  38600000  li r3, 0
 *   801c6e3c  3880007a  li r4, 0x7a
 *   801c6e40  90010014  stw r0, 0x14(r1)
 *   801c6e44  4bf29529  bl 0x800f036c
 *   801c6e48  80010014  lwz r0, 0x14(r1)
 *   801c6e4c  7c0803a6  mtlr r0
 *   801c6e50  38210010  addi r1, r1, 0x10
 *   801c6e54  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 913fc03380b9a10f8381d4da5b10be12abbb300bd7968f9a080bca21f910aa63
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00f036c_(int, int);

void f(void)
{
    zz_00f036c_(0, 0x7a);
}
