/* MATCHED  zz_026e700_ @ 0x8026e700  (2 instructions)
 *
 *   8026e700  9883006d  stb r4, 0x6d(r3)
 *   8026e704  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stb blr
 *   exact_bytes      : true
 *   source sha256    : e09c07cb1bec3c92086afe440f4726e0c8d982dc4349ef117e6262176ef0b8a4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x6d];
    char           field_6d;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_6d = p1;
}
