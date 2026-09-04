/* MATCHED  zz_000314c_ @ 0x8000314c  (2 instructions)
 *
 *   8000314c  886daef8  lbz r3, -0x5108(r13)
 *   80003150  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lbz blr
 *   exact_bytes      : false
 *   source sha256    : 705c9083a7dffa3194f9becf50dedd2022ad328f9052d69768e7f8e18f4292ab
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern unsigned char DAT_80436498;

int f(void)
{
    return DAT_80436498;
}
