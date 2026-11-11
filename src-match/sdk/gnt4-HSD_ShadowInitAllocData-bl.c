/* MATCHED  gnt4-HSD_ShadowInitAllocData-bl @ 0x8025afdc  (12 instructions)
 *
 *   8025afdc  9421fff0  stwu r1, -0x10(r1)
 *   8025afe0  7c0802a6  mflr r0
 *   8025afe4  3c608040  lis r3, -0x7fc0
 *   8025afe8  38800028  li r4, 0x28
 *   8025afec  90010014  stw r0, 0x14(r1)
 *   8025aff0  3863a760  addi r3, r3, -0x58a0
 *   8025aff4  38a00004  li r5, 4
 *   8025aff8  4bffc471  bl 0x80257468
 *   8025affc  80010014  lwz r0, 0x14(r1)
 *   8025b000  7c0803a6  mtlr r0
 *   8025b004  38210010  addi r1, r1, 0x10
 *   8025b008  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3c1da0e21bace62c30f89212df8f16e94d78066b409a9c0cf25c8751f113d2f4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa760;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803fa760, 0x28, 4);
}
