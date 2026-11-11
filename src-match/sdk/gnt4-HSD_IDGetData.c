/* MATCHED  gnt4-HSD_IDGetData @ 0x8024fcfc  (11 instructions)
 *
 *   8024fcfc  9421fff0  stwu r1, -0x10(r1)
 *   8024fd00  7c0802a6  mflr r0
 *   8024fd04  7c852378  mr r5, r4
 *   8024fd08  7c641b78  mr r4, r3
 *   8024fd0c  90010014  stw r0, 0x14(r1)
 *   8024fd10  38600000  li r3, 0
 *   8024fd14  48009b29  bl 0x8025983c
 *   8024fd18  80010014  lwz r0, 0x14(r1)
 *   8024fd1c  7c0803a6  mtlr r0
 *   8024fd20  38210010  addi r1, r1, 0x10
 *   8024fd24  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr mr stw li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 80b9727a3f4901d7e3ac17f3ff6556c0b34f3533d7f016f25b22d35c3cd08314
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8025983c(int, int, int);

void f(int p0, int p1)
{
    FUN_8025983c(0, p0, p1);
}
