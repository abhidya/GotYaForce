/* MATCHED  gnt4-HSD_RObjInitAllocData-bl @ 0x80257598  (17 instructions)
 *
 *   80257598  9421fff0  stwu r1, -0x10(r1)
 *   8025759c  7c0802a6  mflr r0
 *   802575a0  3c608040  lis r3, -0x7fc0
 *   802575a4  3880001c  li r4, 0x1c
 *   802575a8  90010014  stw r0, 0x14(r1)
 *   802575ac  3863a4d8  addi r3, r3, -0x5b28
 *   802575b0  38a00004  li r5, 4
 *   802575b4  4bfffeb5  bl 0x80257468
 *   802575b8  3c608040  lis r3, -0x7fc0
 *   802575bc  3880000c  li r4, 0xc
 *   802575c0  3863a504  addi r3, r3, -0x5afc
 *   802575c4  38a00004  li r5, 4
 *   802575c8  4bfffea1  bl 0x80257468
 *   802575cc  80010014  lwz r0, 0x14(r1)
 *   802575d0  7c0803a6  mtlr r0
 *   802575d4  38210010  addi r1, r1, 0x10
 *   802575d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lis li addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9c7596bb42b69e599f63b1b937570c20539f7f3805a54d9bb90d44d9ac70cae6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa4d8;
extern struct { int v; char pad_[8]; } DAT_803fa504;

extern int FUN_80257468(int, int, int);

int f(void)
{
    FUN_80257468(&DAT_803fa4d8, 0x1c, 4);
    return FUN_80257468(&DAT_803fa504, 0xc, 4);
}
