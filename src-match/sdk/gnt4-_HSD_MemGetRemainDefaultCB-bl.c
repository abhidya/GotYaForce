/* MATCHED  gnt4-_HSD_MemGetRemainDefaultCB-bl @ 0x80254028  (9 instructions)
 *
 *   80254028  9421fff0  stwu r1, -0x10(r1)
 *   8025402c  7c0802a6  mflr r0
 *   80254030  90010014  stw r0, 0x14(r1)
 *   80254034  480000a5  bl 0x802540d8
 *   80254038  4bfabf79  bl 0x801fffb0
 *   8025403c  80010014  lwz r0, 0x14(r1)
 *   80254040  7c0803a6  mtlr r0
 *   80254044  38210010  addi r1, r1, 0x10
 *   80254048  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 713aec5e38da5b203cedaf34f82b332ddd2559c9ef587efe080722961832ffe5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_801fffb0(void);
extern int FUN_802540d8(void);

int f(void)
{
    FUN_802540d8();
    return FUN_801fffb0();
}
