/* MATCHED  zz_0105290_ @ 0x80105290  (10 instructions)
 *
 *   80105290  9421fff0  stwu r1, -0x10(r1)
 *   80105294  7c0802a6  mflr r0
 *   80105298  3c808032  lis r4, -0x7fce
 *   8010529c  90010014  stw r0, 0x14(r1)
 *   801052a0  38841f78  addi r4, r4, 0x1f78
 *   801052a4  4bf6827d  bl 0x8006d520
 *   801052a8  80010014  lwz r0, 0x14(r1)
 *   801052ac  7c0803a6  mtlr r0
 *   801052b0  38210010  addi r1, r1, 0x10
 *   801052b4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c7f96a6c5b9b2c41cf6353fe9fd4479022a4e48eb94dc061f4080262040da939
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80321f78;

extern int zz_006d520_(int, int);

int f(int p0)
{
    return zz_006d520_(p0, &DAT_80321f78);
}
