/* MATCHED  zz_0090cdc_ @ 0x80090cdc  (10 instructions)
 *
 *   80090cdc  9421fff0  stwu r1, -0x10(r1)
 *   80090ce0  7c0802a6  mflr r0
 *   80090ce4  38800000  li r4, 0
 *   80090ce8  38a00040  li r5, 0x40
 *   80090cec  90010014  stw r0, 0x14(r1)
 *   80090cf0  4bf7471d  bl 0x8000540c
 *   80090cf4  80010014  lwz r0, 0x14(r1)
 *   80090cf8  7c0803a6  mtlr r0
 *   80090cfc  38210010  addi r1, r1, 0x10
 *   80090d00  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b7969245e9965d42c899fb280a10bd18857b731a2ae72ab8314fd15cf45300f5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_8000540c(int, int, int);

void f(int p0)
{
    FUN_8000540c(p0, 0, 0x40);
}
