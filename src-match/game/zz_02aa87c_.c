/* MATCHED  zz_02aa87c_ @ 0x802aa87c  (9 instructions)
 *
 *   802aa87c  9421fff0  stwu r1, -0x10(r1)
 *   802aa880  7c0802a6  mflr r0
 *   802aa884  38800000  li r4, 0
 *   802aa888  90010014  stw r0, 0x14(r1)
 *   802aa88c  4bfc3561  bl 0x8026ddec
 *   802aa890  80010014  lwz r0, 0x14(r1)
 *   802aa894  7c0803a6  mtlr r0
 *   802aa898  38210010  addi r1, r1, 0x10
 *   802aa89c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 145b357292682135bc08626297d89542a3bb696406980b8e7b9cfef17fac54cc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_026ddec_(int, int);

void f(int p0)
{
    zz_026ddec_(p0, 0);
}
