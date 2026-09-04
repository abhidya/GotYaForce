/* MATCHED  zz_02aa85c_ @ 0x802aa85c  (8 instructions)
 *
 *   802aa85c  9421fff0  stwu r1, -0x10(r1)
 *   802aa860  7c0802a6  mflr r0
 *   802aa864  90010014  stw r0, 0x14(r1)
 *   802aa868  4bfc32f1  bl 0x8026db58
 *   802aa86c  80010014  lwz r0, 0x14(r1)
 *   802aa870  7c0803a6  mtlr r0
 *   802aa874  38210010  addi r1, r1, 0x10
 *   802aa878  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ae707bf3359d98c70bb4ca0b47768c552722a81877c5538e6f5fdb3cca93a7d8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_026db58_(void);

void f(void)
{
    zz_026db58_();
}
