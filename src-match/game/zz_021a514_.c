/* MATCHED  zz_021a514_ @ 0x8021a514  (2 instructions)
 *
 *   8021a514  806db1f0  lwz r3, -0x4e10(r13)
 *   8021a518  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 1481f31e75e3c4c2479c9df0fa4712d75ee08b0e80fa821d4e5745ce43cf2e46
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436790;

int f(void)
{
    return DAT_80436790;
}
