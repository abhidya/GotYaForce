/* MATCHED  zz_0127544_ @ 0x80127544  (10 instructions)
 *
 *   80127544  9421fff0  stwu r1, -0x10(r1)
 *   80127548  7c0802a6  mflr r0
 *   8012754c  3c808033  lis r4, -0x7fcd
 *   80127550  90010014  stw r0, 0x14(r1)
 *   80127554  388403c8  addi r4, r4, 0x3c8
 *   80127558  480504e5  bl 0x80177a3c
 *   8012755c  80010014  lwz r0, 0x14(r1)
 *   80127560  7c0803a6  mtlr r0
 *   80127564  38210010  addi r1, r1, 0x10
 *   80127568  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ed6229ff52ce72504a378125c37233ecc4abd0e0c942be9b216b79c74e58f546
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803303c8;

extern int zz_0177a3c_(int, int);

int f(int p0)
{
    return zz_0177a3c_(p0, &DAT_803303c8);
}
