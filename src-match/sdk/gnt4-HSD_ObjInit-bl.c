/* MATCHED  gnt4-HSD_ObjInit-bl @ 0x80254288  (17 instructions)
 *
 *   80254288  9421fff0  stwu r1, -0x10(r1)
 *   8025428c  7c0802a6  mflr r0
 *   80254290  90010014  stw r0, 0x14(r1)
 *   80254294  48006865  bl 0x8025aaf8
 *   80254298  4bfef825  bl 0x80243abc
 *   8025429c  4bff44a1  bl 0x8024873c
 *   802542a0  480053a5  bl 0x80259644
 *   802542a4  48002bb5  bl 0x80256e58
 *   802542a8  48002be1  bl 0x80256e88
 *   802542ac  480032ed  bl 0x80257598
 *   802542b0  4bfed60d  bl 0x802418bc
 *   802542b4  48006d29  bl 0x8025afdc
 *   802542b8  4bffe2ed  bl 0x802525a4
 *   802542bc  80010014  lwz r0, 0x14(r1)
 *   802542c0  7c0803a6  mtlr r0
 *   802542c4  38210010  addi r1, r1, 0x10
 *   802542c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl bl bl bl bl bl bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 3093825164763c1b2bf018cabe2baac1889bc4deb07b2ca4d8995406d5f3e28d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_802418bc(void);
extern int FUN_80243abc(void);
extern int FUN_8024873c(void);
extern int FUN_802525a4(void);
extern int FUN_80256e58(void);
extern int FUN_80256e88(void);
extern int FUN_80257598(void);
extern int FUN_80259644(void);
extern int FUN_8025aaf8(void);
extern int FUN_8025afdc(void);

int f(void)
{
    FUN_8025aaf8();
    FUN_80243abc();
    FUN_8024873c();
    FUN_80259644();
    FUN_80256e58();
    FUN_80256e88();
    FUN_80257598();
    FUN_802418bc();
    FUN_8025afdc();
    return FUN_802525a4();
}
