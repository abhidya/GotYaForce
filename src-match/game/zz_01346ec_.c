/* MATCHED  zz_01346ec_ @ 0x801346ec  (10 instructions)
 *
 *   801346ec  9421fff0  stwu r1, -0x10(r1)
 *   801346f0  7c0802a6  mflr r0
 *   801346f4  3c808033  lis r4, -0x7fcd
 *   801346f8  90010014  stw r0, 0x14(r1)
 *   801346fc  38846d94  addi r4, r4, 0x6d94
 *   80134700  4bfd82d9  bl 0x8010c9d8
 *   80134704  80010014  lwz r0, 0x14(r1)
 *   80134708  7c0803a6  mtlr r0
 *   8013470c  38210010  addi r1, r1, 0x10
 *   80134710  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0635b84ea94342060bc3e6eb23be082bad70393e78199ba0752d3f4b2ccbbdba
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80336d94;

extern int zz_010c9d8_(int, int);

int f(int p0)
{
    return zz_010c9d8_(p0, &DAT_80336d94);
}
