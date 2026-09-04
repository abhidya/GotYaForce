/* MATCHED  zz_008d724_ @ 0x8008d724  (2 instructions)
 *
 *   8008d724  806dad14  lwz r3, -0x52ec(r13)
 *   8008d728  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 5271f88c0ba333f945157df7f14f82aa82381fbe983120cdee155be7129f0afd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804362b4;

int f(void)
{
    return DAT_804362b4;
}
