/* MATCHED  gnt4-HSD_JObjAnimAll @ 0x8024ef10  (15 instructions)
 *
 *   8024ef10  9421fff0  stwu r1, -0x10(r1)
 *   8024ef14  7c0802a6  mflr r0
 *   8024ef18  90010014  stw r0, 0x14(r1)
 *   8024ef1c  93e1000c  stw r31, 0xc(r1)
 *   8024ef20  7c7f1b79  or. r31, r3, r3
 *   8024ef24  41820014  beq 0x8024ef38
 *   8024ef28  4bff4bfd  bl 0x80243b24
 *   8024ef2c  7fe3fb78  mr r3, r31
 *   8024ef30  4bfffc99  bl 0x8024ebc8
 *   8024ef34  4bff4c01  bl 0x80243b34
 *   8024ef38  80010014  lwz r0, 0x14(r1)
 *   8024ef3c  83e1000c  lwz r31, 0xc(r1)
 *   8024ef40  7c0803a6  mtlr r0
 *   8024ef44  38210010  addi r1, r1, 0x10
 *   8024ef48  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (3 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 3
 *   shape            : stwu mflr stw stw or. beq bl mr bl bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : bd4d3f3f7efd2cc7753ea18d2484ce24ae70e22e69b22d309729e956fad10868
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_80243b24(void);
extern int FUN_80243b34(void);
extern int FUN_8024ebc8(int);

void f(void * p0)
{
    if (p0 != 0)
    {
        FUN_80243b24();
        FUN_8024ebc8(p0);
        FUN_80243b34();
    }
}
