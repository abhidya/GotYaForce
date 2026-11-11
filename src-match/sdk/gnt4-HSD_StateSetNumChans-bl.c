/* MATCHED  gnt4-HSD_StateSetNumChans-bl @ 0x80241db4  (16 instructions)
 *
 *   80241db4  9421fff0  stwu r1, -0x10(r1)
 *   80241db8  7c0802a6  mflr r0
 *   80241dbc  90010014  stw r0, 0x14(r1)
 *   80241dc0  93e1000c  stw r31, 0xc(r1)
 *   80241dc4  7c7f1b78  mr r31, r3
 *   80241dc8  800db35c  lwz r0, -0x4ca4(r13)
 *   80241dcc  7c00f800  cmpw r0, r31
 *   80241dd0  41820010  beq 0x80241de0
 *   80241dd4  57e3063e  clrlwi r3, r31, 0x18
 *   80241dd8  4bfe6a85  bl 0x8022885c
 *   80241ddc  93edb35c  stw r31, -0x4ca4(r13)
 *   80241de0  80010014  lwz r0, 0x14(r1)
 *   80241de4  83e1000c  lwz r31, 0xc(r1)
 *   80241de8  7c0803a6  mtlr r0
 *   80241dec  38210010  addi r1, r1, 0x10
 *   80241df0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr lwz cmpw beq clrlwi bl stw lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 15dfc2a09414758667a875ffd133e9d931571756ea1d61d672e0415aa6100368
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368fc;

extern int FUN_8022885c(int);

void f(int p0)
{
    if (DAT_804368fc != p0)
    {
        FUN_8022885c(p0 & 0xff);
        DAT_804368fc = p0;
    }
}
