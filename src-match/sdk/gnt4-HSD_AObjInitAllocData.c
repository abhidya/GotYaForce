/* MATCHED  gnt4-HSD_AObjInitAllocData @ 0x80243abc  (12 instructions)
 *
 *   80243abc  9421fff0  stwu r1, -0x10(r1)
 *   80243ac0  7c0802a6  mflr r0
 *   80243ac4  3c608040  lis r3, -0x7fc0
 *   80243ac8  3880001c  li r4, 0x1c
 *   80243acc  90010014  stw r0, 0x14(r1)
 *   80243ad0  38638d90  addi r3, r3, -0x7270
 *   80243ad4  38a00004  li r5, 4
 *   80243ad8  48013991  bl 0x80257468
 *   80243adc  80010014  lwz r0, 0x14(r1)
 *   80243ae0  7c0803a6  mtlr r0
 *   80243ae4  38210010  addi r1, r1, 0x10
 *   80243ae8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7c4d3595502c698ee48952ca6676fbef13f7d9bff1dcf2e2e9a6956ba0c323c5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803f8d90;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803f8d90, 0x1c, 4);
}
