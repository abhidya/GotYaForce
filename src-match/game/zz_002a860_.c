/* MATCHED  zz_002a860_ @ 0x8002a860  (10 instructions)
 *
 *   8002a860  9421fff0  stwu r1, -0x10(r1)
 *   8002a864  7c0802a6  mflr r0
 *   8002a868  7c641b78  mr r4, r3
 *   8002a86c  90010014  stw r0, 0x14(r1)
 *   8002a870  806dac94  lwz r3, -0x536c(r13)
 *   8002a874  481d54c5  bl 0x801ffd38
 *   8002a878  80010014  lwz r0, 0x14(r1)
 *   8002a87c  7c0803a6  mtlr r0
 *   8002a880  38210010  addi r1, r1, 0x10
 *   8002a884  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9a3cc57c93d05e96d2f7e6c4b13f731d417a4ad1ece83d00d0c3e3a49b614664
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436234;

extern int FUN_801ffd38(int, int);

int f(int p0)
{
    return FUN_801ffd38(DAT_80436234, p0);
}
