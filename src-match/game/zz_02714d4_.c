/* MATCHED  zz_02714d4_ @ 0x802714d4  (8 instructions)
 *
 *   802714d4  9421fff0  stwu r1, -0x10(r1)
 *   802714d8  7c0802a6  mflr r0
 *   802714dc  90010014  stw r0, 0x14(r1)
 *   802714e0  480089e5  bl 0x80279ec4
 *   802714e4  80010014  lwz r0, 0x14(r1)
 *   802714e8  7c0803a6  mtlr r0
 *   802714ec  38210010  addi r1, r1, 0x10
 *   802714f0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : fc7a7a36144ea8eb1df9fdfcab1676887ef790cdc4c37c7c56cf267b576a4b7d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0279ec4_(void);

void f(void)
{
    zz_0279ec4_();
}
