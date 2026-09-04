/* MATCHED  zz_0181dd8_ @ 0x80181dd8  (9 instructions)
 *
 *   80181dd8  9421fff0  stwu r1, -0x10(r1)
 *   80181ddc  7c0802a6  mflr r0
 *   80181de0  90010014  stw r0, 0x14(r1)
 *   80181de4  48000019  bl 0x80181dfc
 *   80181de8  48000049  bl 0x80181e30
 *   80181dec  80010014  lwz r0, 0x14(r1)
 *   80181df0  7c0803a6  mtlr r0
 *   80181df4  38210010  addi r1, r1, 0x10
 *   80181df8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 28c726b02d97bde3696632e58fa6df0ecc6f0a6a3701d18b3296e84905f3e353
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0181dfc_(void);
extern int zz_0181e30_(void);

int f(void)
{
    zz_0181dfc_();
    return zz_0181e30_();
}
