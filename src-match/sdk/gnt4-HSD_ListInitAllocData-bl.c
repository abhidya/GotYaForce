/* MATCHED  gnt4-HSD_ListInitAllocData-bl @ 0x8025aaf8  (17 instructions)
 *
 *   8025aaf8  9421fff0  stwu r1, -0x10(r1)
 *   8025aafc  7c0802a6  mflr r0
 *   8025ab00  3c608040  lis r3, -0x7fc0
 *   8025ab04  38800008  li r4, 8
 *   8025ab08  90010014  stw r0, 0x14(r1)
 *   8025ab0c  3863a6f0  addi r3, r3, -0x5910
 *   8025ab10  38a00004  li r5, 4
 *   8025ab14  4bffc955  bl 0x80257468
 *   8025ab18  3c608040  lis r3, -0x7fc0
 *   8025ab1c  3880000c  li r4, 0xc
 *   8025ab20  3863a71c  addi r3, r3, -0x58e4
 *   8025ab24  38a00004  li r5, 4
 *   8025ab28  4bffc941  bl 0x80257468
 *   8025ab2c  80010014  lwz r0, 0x14(r1)
 *   8025ab30  7c0803a6  mtlr r0
 *   8025ab34  38210010  addi r1, r1, 0x10
 *   8025ab38  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lis li addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5cf894c12869c7d663e080846924d7b9669b7ba92e3bc69ea43af5ad5392b85e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa6f0;
extern struct { int v; char pad_[8]; } DAT_803fa71c;

extern int FUN_80257468(int, int, int);

int f(void)
{
    FUN_80257468(&DAT_803fa6f0, 8, 4);
    return FUN_80257468(&DAT_803fa71c, 0xc, 4);
}
