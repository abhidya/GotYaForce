/* MATCHED  zz_0112f00_ @ 0x80112f00  (10 instructions)
 *
 *   80112f00  9421fff0  stwu r1, -0x10(r1)
 *   80112f04  7c0802a6  mflr r0
 *   80112f08  3c808032  lis r4, -0x7fce
 *   80112f0c  90010014  stw r0, 0x14(r1)
 *   80112f10  38847f48  addi r4, r4, 0x7f48
 *   80112f14  4bfdef1d  bl 0x800f1e30
 *   80112f18  80010014  lwz r0, 0x14(r1)
 *   80112f1c  7c0803a6  mtlr r0
 *   80112f20  38210010  addi r1, r1, 0x10
 *   80112f24  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 463ad14c1f511a4ed8bb981d626538bb3f618612bad83aa8248b489a66ca607d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80327f48;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_80327f48);
}
