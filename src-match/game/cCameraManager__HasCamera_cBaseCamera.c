/* MATCHED  cCameraManager::HasCamera(cBaseCamera @ 0x80008998  (10 instructions)
 *
 *   80008998  9421fff0  stwu r1, -0x10(r1)
 *   8000899c  7c0802a6  mflr r0
 *   800089a0  7c641b78  mr r4, r3
 *   800089a4  90010014  stw r0, 0x14(r1)
 *   800089a8  806dac70  lwz r3, -0x5390(r13)
 *   800089ac  4823e781  bl 0x8024712c
 *   800089b0  80010014  lwz r0, 0x14(r1)
 *   800089b4  7c0803a6  mtlr r0
 *   800089b8  38210010  addi r1, r1, 0x10
 *   800089bc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr mr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 595b2203564cdbedaca43fd1a1e68e499e527a5767e5bc2b5e4b61a2ddb334f2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436210;

extern int FUN_8024712c(int, int);

int f(int p0)
{
    return FUN_8024712c(DAT_80436210, p0);
}
