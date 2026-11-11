/* MATCHED  zz_02598c4_ @ 0x802598c4  (12 instructions)
 *
 *   802598c4  9421fff0  stwu r1, -0x10(r1)
 *   802598c8  7c0802a6  mflr r0
 *   802598cc  3c608040  lis r3, -0x7fc0
 *   802598d0  38800000  li r4, 0
 *   802598d4  90010014  stw r0, 0x14(r1)
 *   802598d8  3863a55c  addi r3, r3, -0x5aa4
 *   802598dc  38a00194  li r5, 0x194
 *   802598e0  4bdabb2d  bl 0x8000540c
 *   802598e4  80010014  lwz r0, 0x14(r1)
 *   802598e8  7c0803a6  mtlr r0
 *   802598ec  38210010  addi r1, r1, 0x10
 *   802598f0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ccf0af26198edd4221570151929bded10fa81e82dec133bbcfef0e93b58402b3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa55c;

extern int FUN_8000540c(int, int, int);

int f(void)
{
    return FUN_8000540c(&DAT_803fa55c, 0, 0x194);
}
