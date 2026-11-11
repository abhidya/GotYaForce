/* MATCHED  gnt4-HSD_ZListInitAllocData-bl @ 0x802525a4  (12 instructions)
 *
 *   802525a4  9421fff0  stwu r1, -0x10(r1)
 *   802525a8  7c0802a6  mflr r0
 *   802525ac  3c608040  lis r3, -0x7fc0
 *   802525b0  38800048  li r4, 0x48
 *   802525b4  90010014  stw r0, 0x14(r1)
 *   802525b8  38638e28  addi r3, r3, -0x71d8
 *   802525bc  38a00004  li r5, 4
 *   802525c0  48004ea9  bl 0x80257468
 *   802525c4  80010014  lwz r0, 0x14(r1)
 *   802525c8  7c0803a6  mtlr r0
 *   802525cc  38210010  addi r1, r1, 0x10
 *   802525d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9ee500ca34a5a5cf68d87ff1a2228d971c05be4a929fc0f9c9b29bd89ed01503
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803f8e28;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803f8e28, 0x48, 4);
}
