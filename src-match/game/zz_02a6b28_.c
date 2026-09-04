/* MATCHED  zz_02a6b28_ @ 0x802a6b28  (2 instructions)
 *
 *   802a6b28  90830000  stw r4, 0(r3)
 *   802a6b2c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 73cd3104cd97848472513b70487586912f617ff98633585c981a6cfb0252f6e9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_0 = p1;
}
