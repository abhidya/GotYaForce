/* MATCHED  gnt4-HSD_ClearVtxDesc-bl @ 0x8024ac80  (11 instructions)
 *
 *   8024ac80  9421fff0  stwu r1, -0x10(r1)
 *   8024ac84  7c0802a6  mflr r0
 *   8024ac88  90010014  stw r0, 0x14(r1)
 *   8024ac8c  4bfdb521  bl 0x802261ac
 *   8024ac90  38000000  li r0, 0
 *   8024ac94  900db3d4  stw r0, -0x4c2c(r13)
 *   8024ac98  900db3d8  stw r0, -0x4c28(r13)
 *   8024ac9c  80010014  lwz r0, 0x14(r1)
 *   8024aca0  7c0803a6  mtlr r0
 *   8024aca4  38210010  addi r1, r1, 0x10
 *   8024aca8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li stw stw lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 52f99ea4cc6b0ea46fea3c40a8e3dd0e532036e8405bc9f65f008eba2a6ab200
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436974;
extern int DAT_80436978;

extern int FUN_802261ac(void);

void f(void)
{
    FUN_802261ac();
    DAT_80436974 = 0;
    DAT_80436978 = 0;
}
