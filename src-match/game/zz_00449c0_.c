/* MATCHED  zz_00449c0_ @ 0x800449c0  (10 instructions)
 *
 *   800449c0  9421fff0  stwu r1, -0x10(r1)
 *   800449c4  7c0802a6  mflr r0
 *   800449c8  38600000  li r3, 0
 *   800449cc  90010014  stw r0, 0x14(r1)
 *   800449d0  808dac98  lwz r4, -0x5368(r13)
 *   800449d4  4bfc65b1  bl 0x8000af84
 *   800449d8  80010014  lwz r0, 0x14(r1)
 *   800449dc  7c0803a6  mtlr r0
 *   800449e0  38210010  addi r1, r1, 0x10
 *   800449e4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b1a8f3832c41945ee1ef926e36045c2501fa30b07d57c8fa308941b7ec93ee7b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436238;

extern int zz_000af84_(int, int);

int f(void)
{
    return zz_000af84_(0, DAT_80436238);
}
