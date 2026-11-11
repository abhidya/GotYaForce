/* MATCHED  gnt4-HSD_StateSetCullMode-bl @ 0x80241420  (15 instructions)
 *
 *   80241420  9421fff0  stwu r1, -0x10(r1)
 *   80241424  7c0802a6  mflr r0
 *   80241428  90010014  stw r0, 0x14(r1)
 *   8024142c  93e1000c  stw r31, 0xc(r1)
 *   80241430  7c7f1b78  mr r31, r3
 *   80241434  800db34c  lwz r0, -0x4cb4(r13)
 *   80241438  7c00f800  cmpw r0, r31
 *   8024143c  4182000c  beq 0x80241448
 *   80241440  4bfe63ed  bl 0x8022782c
 *   80241444  93edb34c  stw r31, -0x4cb4(r13)
 *   80241448  80010014  lwz r0, 0x14(r1)
 *   8024144c  83e1000c  lwz r31, 0xc(r1)
 *   80241450  7c0803a6  mtlr r0
 *   80241454  38210010  addi r1, r1, 0x10
 *   80241458  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr lwz cmpw beq bl stw lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 66dd974c7241c47d5bc4fc2a8a579908bf19352836ed802cd80311a1f9975fd2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368ec;

extern int FUN_8022782c(void);

void f(int p0)
{
    if (DAT_804368ec != p0)
    {
        FUN_8022782c();
        DAT_804368ec = p0;
    }
}
