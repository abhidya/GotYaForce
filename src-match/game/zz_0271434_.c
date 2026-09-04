/* MATCHED  zz_0271434_ @ 0x80271434  (8 instructions)
 *
 *   80271434  9421fff0  stwu r1, -0x10(r1)
 *   80271438  7c0802a6  mflr r0
 *   8027143c  90010014  stw r0, 0x14(r1)
 *   80271440  480081b9  bl 0x802795f8
 *   80271444  80010014  lwz r0, 0x14(r1)
 *   80271448  7c0803a6  mtlr r0
 *   8027144c  38210010  addi r1, r1, 0x10
 *   80271450  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6b850cc483182c045ec5dc34fe8c9419b60887bb057b9a3ce24b451f03f12e04
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02795f8_(void);

void f(void)
{
    zz_02795f8_();
}
