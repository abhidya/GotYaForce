/* MATCHED  zz_02683cc_ @ 0x802683cc  (2 instructions)
 *
 *   802683cc  8063002c  lwz r3, 0x2c(r3)
 *   802683d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 6dd2c009a03ed8fff0608382458d2baf90d2ddc9e0da04fd9389cc2af1b6a7a4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x2c];
    int            field_2c;
} S0;

int f(S0 *p0)
{
    return p0->field_2c;
}
