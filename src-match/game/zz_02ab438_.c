/* MATCHED  zz_02ab438_ @ 0x802ab438  (8 instructions)
 *
 *   802ab438  9421fff0  stwu r1, -0x10(r1)
 *   802ab43c  7c0802a6  mflr r0
 *   802ab440  90010014  stw r0, 0x14(r1)
 *   802ab444  4bfd0171  bl 0x8027b5b4
 *   802ab448  80010014  lwz r0, 0x14(r1)
 *   802ab44c  7c0803a6  mtlr r0
 *   802ab450  38210010  addi r1, r1, 0x10
 *   802ab454  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5201c37c95d8caa7d0b8fda0b3b325a8a0c2c43ed90d3726faed24ca182eb8c9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027b5b4_(void);

void f(void)
{
    zz_027b5b4_();
}
