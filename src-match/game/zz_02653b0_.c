/* MATCHED  zz_02653b0_ @ 0x802653b0  (12 instructions)
 *
 *   802653b0  9421fff0  stwu r1, -0x10(r1)
 *   802653b4  7c0802a6  mflr r0
 *   802653b8  3c608040  lis r3, -0x7fc0
 *   802653bc  38800000  li r4, 0
 *   802653c0  90010014  stw r0, 0x14(r1)
 *   802653c4  3863b670  addi r3, r3, -0x4990
 *   802653c8  38a009c0  li r5, 0x9c0
 *   802653cc  4bda0041  bl 0x8000540c
 *   802653d0  80010014  lwz r0, 0x14(r1)
 *   802653d4  7c0803a6  mtlr r0
 *   802653d8  38210010  addi r1, r1, 0x10
 *   802653dc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e92a7590e86555b5ecc01e94ccded88e7822b79357d55209330e9b2e8d33c6ed
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fb670;

extern int FUN_8000540c(int, int, int);

int f(void)
{
    return FUN_8000540c(&DAT_803fb670, 0, 0x9c0);
}
