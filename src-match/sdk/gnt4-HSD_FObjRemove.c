/* MATCHED  gnt4-HSD_FObjRemove @ 0x8024876c  (10 instructions)
 *
 *   8024876c  9421fff0  stwu r1, -0x10(r1)
 *   80248770  7c0802a6  mflr r0
 *   80248774  28030000  cmplwi r3, 0
 *   80248778  90010014  stw r0, 0x14(r1)
 *   8024877c  41820008  beq 0x80248784
 *   80248780  48001d0d  bl 0x8024a48c
 *   80248784  80010014  lwz r0, 0x14(r1)
 *   80248788  7c0803a6  mtlr r0
 *   8024878c  38210010  addi r1, r1, 0x10
 *   80248790  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : stwu mflr cmplwi stw beq bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7a1ee4382d3d73801ada17452fda6e51389c7fa4bec8654f8137424d43c76319
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_8024a48c(void);

void f(unsigned int p0)
{
    if (p0 != 0)
        FUN_8024a48c();
}
