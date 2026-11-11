/* MATCHED  zz_01260c8_ @ 0x801260c8  (10 instructions)
 *
 *   801260c8  9421fff0  stwu r1, -0x10(r1)
 *   801260cc  7c0802a6  mflr r0
 *   801260d0  3c808033  lis r4, -0x7fcd
 *   801260d4  90010014  stw r0, 0x14(r1)
 *   801260d8  3884f48c  addi r4, r4, -0xb74
 *   801260dc  48054299  bl 0x8017a374
 *   801260e0  80010014  lwz r0, 0x14(r1)
 *   801260e4  7c0803a6  mtlr r0
 *   801260e8  38210010  addi r1, r1, 0x10
 *   801260ec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c81259e0c7a945c941a792de5af7391ca2f75ca0adda425653fffff7b500bc5d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8032f48c;

extern int zz_017a374_(int, int);

int f(int p0)
{
    return zz_017a374_(p0, &DAT_8032f48c);
}
