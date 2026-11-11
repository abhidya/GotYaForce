/* MATCHED  gnt4-HSD_MtxInitAllocData-bl @ 0x80256e88  (12 instructions)
 *
 *   80256e88  9421fff0  stwu r1, -0x10(r1)
 *   80256e8c  7c0802a6  mflr r0
 *   80256e90  3c608040  lis r3, -0x7fc0
 *   80256e94  38800030  li r4, 0x30
 *   80256e98  90010014  stw r0, 0x14(r1)
 *   80256e9c  3863a4ac  addi r3, r3, -0x5b54
 *   80256ea0  38a00004  li r5, 4
 *   80256ea4  480005c5  bl 0x80257468
 *   80256ea8  80010014  lwz r0, 0x14(r1)
 *   80256eac  7c0803a6  mtlr r0
 *   80256eb0  38210010  addi r1, r1, 0x10
 *   80256eb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3c05c9d4c758dc3011e38838220ae6794203e0db11cbcd04d5ab7db7ef5fcc23
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa4ac;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803fa4ac, 0x30, 4);
}
