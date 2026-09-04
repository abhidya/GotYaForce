/* MATCHED  zz_0273868_ @ 0x80273868  (8 instructions)
 *
 *   80273868  9421fff0  stwu r1, -0x10(r1)
 *   8027386c  7c0802a6  mflr r0
 *   80273870  90010014  stw r0, 0x14(r1)
 *   80273874  4bfffc55  bl 0x802734c8
 *   80273878  80010014  lwz r0, 0x14(r1)
 *   8027387c  7c0803a6  mtlr r0
 *   80273880  38210010  addi r1, r1, 0x10
 *   80273884  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d97101c0eda16224f6b81bb6c3cf877df0d8444d733c606a8e549d17c3427bd0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02734c8_(void);

void f(void)
{
    zz_02734c8_();
}
