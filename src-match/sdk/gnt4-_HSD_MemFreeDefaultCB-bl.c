/* MATCHED  gnt4-_HSD_MemFreeDefaultCB-bl @ 0x80253ff4  (13 instructions)
 *
 *   80253ff4  9421fff0  stwu r1, -0x10(r1)
 *   80253ff8  7c0802a6  mflr r0
 *   80253ffc  90010014  stw r0, 0x14(r1)
 *   80254000  93e1000c  stw r31, 0xc(r1)
 *   80254004  7c7f1b78  mr r31, r3
 *   80254008  480000d1  bl 0x802540d8
 *   8025400c  7fe4fb78  mr r4, r31
 *   80254010  4bfabe25  bl 0x801ffe34
 *   80254014  80010014  lwz r0, 0x14(r1)
 *   80254018  83e1000c  lwz r31, 0xc(r1)
 *   8025401c  7c0803a6  mtlr r0
 *   80254020  38210010  addi r1, r1, 0x10
 *   80254024  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl mr bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 850853d9248db27e54dad53b9023b8e9dbb09f8c498b153626b8a3587aaad8ae
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_801ffe34(int, int);
extern int FUN_802540d8(void);

int f(int p0)
{
    return FUN_801ffe34(FUN_802540d8(), p0);
}
