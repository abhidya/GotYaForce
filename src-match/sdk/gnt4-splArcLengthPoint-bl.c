/* MATCHED  gnt4-splArcLengthPoint-bl @ 0x80255a48  (18 instructions)
 *
 *   80255a48  9421fff0  stwu r1, -0x10(r1)
 *   80255a4c  7c0802a6  mflr r0
 *   80255a50  90010014  stw r0, 0x14(r1)
 *   80255a54  93e1000c  stw r31, 0xc(r1)
 *   80255a58  7c9f2378  mr r31, r4
 *   80255a5c  93c10008  stw r30, 8(r1)
 *   80255a60  7c7e1b78  mr r30, r3
 *   80255a64  7fe3fb78  mr r3, r31
 *   80255a68  4bfffde1  bl 0x80255848
 *   80255a6c  7fc3f378  mr r3, r30
 *   80255a70  7fe4fb78  mr r4, r31
 *   80255a74  4bfff63d  bl 0x802550b0
 *   80255a78  80010014  lwz r0, 0x14(r1)
 *   80255a7c  83e1000c  lwz r31, 0xc(r1)
 *   80255a80  83c10008  lwz r30, 8(r1)
 *   80255a84  7c0803a6  mtlr r0
 *   80255a88  38210010  addi r1, r1, 0x10
 *   80255a8c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr stw mr mr bl mr mr bl lwz lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 037541d0a1b6ec2e9dbe4af556ff9d67b820f6ea53d35ac835a61eff381bd444
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_802550b0(int, int);
extern int FUN_80255848(int);

int f(int p0, int p1)
{
    FUN_80255848(p1);
    return FUN_802550b0(p0, p1);
}
