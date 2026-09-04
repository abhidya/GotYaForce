/* MATCHED  gnt4-HSD_CObjGetCurrent @ 0x80248194  (2 instructions)
 *
 *   80248194  806db3bc  lwz r3, -0x4c44(r13)
 *   80248198  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 4cf9d37be85ec0774aced48e6dcff04f283f4efe0d042a2d99dacc3d48426eeb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043695c;

int f(void)
{
    return DAT_8043695c;
}
