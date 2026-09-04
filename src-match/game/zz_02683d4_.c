/* MATCHED  zz_02683d4_ @ 0x802683d4  (2 instructions)
 *
 *   802683d4  80630028  lwz r3, 0x28(r3)
 *   802683d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 880a5a1b1f65132b6b5c05ed061be2560be91709019028642e5225439006ed22
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x28];
    int            field_28;
} S0;

int f(S0 *p0)
{
    return p0->field_28;
}
