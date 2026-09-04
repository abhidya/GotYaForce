/* MATCHED  zz_00f07c4_ @ 0x800f07c4  (9 instructions)
 *
 *   800f07c4  9421fff0  stwu r1, -0x10(r1)
 *   800f07c8  7c0802a6  mflr r0
 *   800f07cc  90010014  stw r0, 0x14(r1)
 *   800f07d0  4bfff6a1  bl 0x800efe70
 *   800f07d4  48000d01  bl 0x800f14d4
 *   800f07d8  80010014  lwz r0, 0x14(r1)
 *   800f07dc  7c0803a6  mtlr r0
 *   800f07e0  38210010  addi r1, r1, 0x10
 *   800f07e4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4c08e06cf9e9ff99d84a25791832038b05a133d7344539b779b75026eb5fc7cc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_00efe70_(void);
extern int zz_00f14d4_(void);

int f(void)
{
    zz_00efe70_();
    return zz_00f14d4_();
}
