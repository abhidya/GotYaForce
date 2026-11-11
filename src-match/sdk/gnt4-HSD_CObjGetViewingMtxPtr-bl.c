/* MATCHED  gnt4-HSD_CObjGetViewingMtxPtr-bl @ 0x80247c00  (12 instructions)
 *
 *   80247c00  9421fff0  stwu r1, -0x10(r1)
 *   80247c04  7c0802a6  mflr r0
 *   80247c08  90010014  stw r0, 0x14(r1)
 *   80247c0c  93e1000c  stw r31, 0xc(r1)
 *   80247c10  7c7f1b78  mr r31, r3
 *   80247c14  4bffeea5  bl 0x80246ab8
 *   80247c18  80010014  lwz r0, 0x14(r1)
 *   80247c1c  387f0054  addi r3, r31, 0x54
 *   80247c20  83e1000c  lwz r31, 0xc(r1)
 *   80247c24  7c0803a6  mtlr r0
 *   80247c28  38210010  addi r1, r1, 0x10
 *   80247c2c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl lwz addi lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : fa0c479b8d1ac77c12aa20ea9e527cd625234bbaaf8650733869f320f0a467d1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_80246ab8(void);

int f(int p0)
{
    FUN_80246ab8();
    return p0 + 0x54;
}
