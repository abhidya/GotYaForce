/* MATCHED  zz_02aa7dc_ @ 0x802aa7dc  (8 instructions)
 *
 *   802aa7dc  9421fff0  stwu r1, -0x10(r1)
 *   802aa7e0  7c0802a6  mflr r0
 *   802aa7e4  90010014  stw r0, 0x14(r1)
 *   802aa7e8  4bfc2f31  bl 0x8026d718
 *   802aa7ec  80010014  lwz r0, 0x14(r1)
 *   802aa7f0  7c0803a6  mtlr r0
 *   802aa7f4  38210010  addi r1, r1, 0x10
 *   802aa7f8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c619ff53cde2341a0007347dbac824fdbd2d3c29d97172b64a62c7d9eeccacd6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_026d718_(void);

void f(void)
{
    zz_026d718_();
}
