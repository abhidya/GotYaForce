/* MATCHED  zz_018cb20_ @ 0x8018cb20  (10 instructions)
 *
 *   8018cb20  9421fff0  stwu r1, -0x10(r1)
 *   8018cb24  7c0802a6  mflr r0
 *   8018cb28  3c808036  lis r4, -0x7fca
 *   8018cb2c  90010014  stw r0, 0x14(r1)
 *   8018cb30  38845510  addi r4, r4, 0x5510
 *   8018cb34  4bfed841  bl 0x8017a374
 *   8018cb38  80010014  lwz r0, 0x14(r1)
 *   8018cb3c  7c0803a6  mtlr r0
 *   8018cb40  38210010  addi r1, r1, 0x10
 *   8018cb44  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 126092d488706919535aec64869edc854571f40b773206c21661091139c7458a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80365510;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_80365510);
}
