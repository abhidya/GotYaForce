/* MATCHED  zz_005f554_ @ 0x8005f554  (9 instructions)
 *
 *   8005f554  9421fff0  stwu r1, -0x10(r1)
 *   8005f558  7c0802a6  mflr r0
 *   8005f55c  3880000d  li r4, 0xd
 *   8005f560  90010014  stw r0, 0x14(r1)
 *   8005f564  4bfed7c1  bl 0x8004cd24
 *   8005f568  80010014  lwz r0, 0x14(r1)
 *   8005f56c  7c0803a6  mtlr r0
 *   8005f570  38210010  addi r1, r1, 0x10
 *   8005f574  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : cc54fb632cbe8b624204d2d4ed33c7abe4173f0867c85d0fead561cbfdac2500
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_004cd24_(int, int);

void f(int p0)
{
    zz_004cd24_(p0, 0xd);
}
