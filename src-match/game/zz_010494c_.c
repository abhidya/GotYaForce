/* MATCHED  zz_010494c_ @ 0x8010494c  (3 instructions)
 *
 *   8010494c  38000003  li r0, 3
 *   80104950  98030018  stb r0, 0x18(r3)
 *   80104954  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : true
 *   source sha256    : 76d789bd5f3c360ac5cbfc618d434b0e683a7a81a79783be71a17614b2a20124
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x18];
    char           field_18;
} S0;

void f(S0 *p0)
{
    p0->field_18 = 3;
}
