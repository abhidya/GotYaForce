/* MATCHED  zz_02aa60c_ @ 0x802aa60c  (8 instructions)
 *
 *   802aa60c  9421fff0  stwu r1, -0x10(r1)
 *   802aa610  7c0802a6  mflr r0
 *   802aa614  90010014  stw r0, 0x14(r1)
 *   802aa618  4bfce0ad  bl 0x802786c4
 *   802aa61c  80010014  lwz r0, 0x14(r1)
 *   802aa620  7c0803a6  mtlr r0
 *   802aa624  38210010  addi r1, r1, 0x10
 *   802aa628  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c64f04741a4a4293daf31e485577e33e9b769d989d229cf84ab6d084eb245773
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02786c4_(void);

void f(void)
{
    zz_02786c4_();
}
