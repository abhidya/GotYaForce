/* MATCHED  zz_0276e14_ @ 0x80276e14  (2 instructions)
 *
 *   80276e14  80630024  lwz r3, 0x24(r3)
 *   80276e18  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : d27a7fb02edcb5f1bf4cb31406d8b31d2341eb773d526e649c2cdf292808a20c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x24];
    int            field_24;
} S0;

int f(S0 *p0)
{
    return p0->field_24;
}
