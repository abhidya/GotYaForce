/* MATCHED  gnt4-HSD_FObjInitAllocData @ 0x8024873c  (12 instructions)
 *
 *   8024873c  9421fff0  stwu r1, -0x10(r1)
 *   80248740  7c0802a6  mflr r0
 *   80248744  3c608040  lis r3, -0x7fc0
 *   80248748  38800030  li r4, 0x30
 *   8024874c  90010014  stw r0, 0x14(r1)
 *   80248750  38638de8  addi r3, r3, -0x7218
 *   80248754  38a00004  li r5, 4
 *   80248758  4800ed11  bl 0x80257468
 *   8024875c  80010014  lwz r0, 0x14(r1)
 *   80248760  7c0803a6  mtlr r0
 *   80248764  38210010  addi r1, r1, 0x10
 *   80248768  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6eeac19be3792602a8f1391d2ffbb7208577bf0f9b43f03df46d31059d6f83d8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803f8de8;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803f8de8, 0x30, 4);
}
