/* MATCHED  zz_026481c_ @ 0x8026481c  (2 instructions)
 *
 *   8026481c  9083003c  stw r4, 0x3c(r3)
 *   80264820  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 636a4ffdd943dfe54c30cfeb34da8805868855848e06d505bf2b023a4cf24d7e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x3c];
    int            field_3c;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_3c = p1;
}
