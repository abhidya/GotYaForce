/* MATCHED  zz_0112fe8_ @ 0x80112fe8  (10 instructions)
 *
 *   80112fe8  9421fff0  stwu r1, -0x10(r1)
 *   80112fec  7c0802a6  mflr r0
 *   80112ff0  3c808032  lis r4, -0x7fce
 *   80112ff4  90010014  stw r0, 0x14(r1)
 *   80112ff8  38847f5c  addi r4, r4, 0x7f5c
 *   80112ffc  4bfdee35  bl 0x800f1e30
 *   80113000  80010014  lwz r0, 0x14(r1)
 *   80113004  7c0803a6  mtlr r0
 *   80113008  38210010  addi r1, r1, 0x10
 *   8011300c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a50714d17131e1323b7da0857f88869db56ce4505f57e7539b35d883388faf1d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80327f5c;

extern int zz_00f1e30_(int, int);

int f(int p0)
{
    return zz_00f1e30_(p0, &DAT_80327f5c);
}
