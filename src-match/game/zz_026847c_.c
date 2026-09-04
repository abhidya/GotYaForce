/* MATCHED  zz_026847c_ @ 0x8026847c  (2 instructions)
 *
 *   8026847c  8063003c  lwz r3, 0x3c(r3)
 *   80268480  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 641d8637127e18455614e26d0c9f89f91a87afa8d5711f91b225fb748ade8241
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x3c];
    int            field_3c;
} S0;

int f(S0 *p0)
{
    return p0->field_3c;
}
