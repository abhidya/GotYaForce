/* MATCHED  zz_0268474_ @ 0x80268474  (2 instructions)
 *
 *   80268474  a8630098  lha r3, 0x98(r3)
 *   80268478  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha blr
 *   exact_bytes      : true
 *   source sha256    : 31fe378c2c4566f3a45f141afd295920fa36c2cab025eedafa91110a3e1bf41a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x98];
    short          field_98;
} S0;

int f(S0 *p0)
{
    return p0->field_98;
}
