/* MATCHED  zz_0057fc8_ @ 0x80057fc8  (2 instructions)
 *
 *   80057fc8  b0830072  sth r4, 0x72(r3)
 *   80057fcc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : sth blr
 *   exact_bytes      : true
 *   source sha256    : 221d65a21d7ec6b1c7a0fbf7a8c6e434ab969282f949e0044dba8113d5309d41
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x72];
    short          field_72;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_72 = p1;
}
