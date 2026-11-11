/* MATCHED  gnt4-HSD_JObjReqAnimAll @ 0x8024db88  (9 instructions)
 *
 *   8024db88  9421fff0  stwu r1, -0x10(r1)
 *   8024db8c  7c0802a6  mflr r0
 *   8024db90  388007ff  li r4, 0x7ff
 *   8024db94  90010014  stw r0, 0x14(r1)
 *   8024db98  4bfffd29  bl 0x8024d8c0
 *   8024db9c  80010014  lwz r0, 0x14(r1)
 *   8024dba0  7c0803a6  mtlr r0
 *   8024dba4  38210010  addi r1, r1, 0x10
 *   8024dba8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ef265a717898579c58db05b6494382064b9c31a9cea9fdf5e5efdc967b1ec9ae
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8024d8c0(int, int);

void f(int p0)
{
    FUN_8024d8c0(p0, 0x7ff);
}
