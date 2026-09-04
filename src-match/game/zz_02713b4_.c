/* MATCHED  zz_02713b4_ @ 0x802713b4  (8 instructions)
 *
 *   802713b4  9421fff0  stwu r1, -0x10(r1)
 *   802713b8  7c0802a6  mflr r0
 *   802713bc  90010014  stw r0, 0x14(r1)
 *   802713c0  480080b9  bl 0x80279478
 *   802713c4  80010014  lwz r0, 0x14(r1)
 *   802713c8  7c0803a6  mtlr r0
 *   802713cc  38210010  addi r1, r1, 0x10
 *   802713d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c9ac36a760a0790e02132af510d86cc81b55de3c5dc7dd5e4e4d5b037ea6fdcb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279478_(void);

void f(void)
{
    zz_0279478_();
}
