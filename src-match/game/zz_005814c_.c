/* MATCHED  zz_005814c_ @ 0x8005814c  (5 instructions)
 *
 *   8005814c  b08303ea  sth r4, 0x3ea(r3)
 *   80058150  b08303e8  sth r4, 0x3e8(r3)
 *   80058154  98a303ed  stb r5, 0x3ed(r3)
 *   80058158  98a303ec  stb r5, 0x3ec(r3)
 *   8005815c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : sth sth stb stb blr
 *   exact_bytes      : true
 *   source sha256    : ae098a5258b55cca3104553edd252d08b9a68fa55640f79eb5e95dda6a1d67f2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x3e8];
    short          field_3e8;
    short          field_3ea;
    char           field_3ec;
    char           field_3ed;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_3ea = p1;
    p0->field_3e8 = p1;
    p0->field_3ed = p2;
    p0->field_3ec = p2;
}
