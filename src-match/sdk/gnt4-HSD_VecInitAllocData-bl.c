/* MATCHED  gnt4-HSD_VecInitAllocData-bl @ 0x80256e58  (12 instructions)
 *
 *   80256e58  9421fff0  stwu r1, -0x10(r1)
 *   80256e5c  7c0802a6  mflr r0
 *   80256e60  3c608040  lis r3, -0x7fc0
 *   80256e64  3880000c  li r4, 0xc
 *   80256e68  90010014  stw r0, 0x14(r1)
 *   80256e6c  3863a480  addi r3, r3, -0x5b80
 *   80256e70  38a00004  li r5, 4
 *   80256e74  480005f5  bl 0x80257468
 *   80256e78  80010014  lwz r0, 0x14(r1)
 *   80256e7c  7c0803a6  mtlr r0
 *   80256e80  38210010  addi r1, r1, 0x10
 *   80256e84  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a263b12250976a48bda4e3c83e026ea128674d018ad4674a65a875e8d367a8a2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa480;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803fa480, 0xc, 4);
}
