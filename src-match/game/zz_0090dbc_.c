/* MATCHED  zz_0090dbc_ @ 0x80090dbc  (3 instructions)
 *
 *   80090dbc  54601838  slwi r0, r3, 3
 *   80090dc0  9004003c  stw r0, 0x3c(r4)
 *   80090dc4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : slwi stw blr
 *   exact_bytes      : true
 *   source sha256    : b71ce1525e352448637349a03ea7415af0aa34ce30fb0bece37beb961baae3ac
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S1 {
    char pad_0[0x3c];
    int                  field_3c;
} S1;

void f(int p0, S1 *p1)
{
    p1->field_3c = p0 << 3;
}
