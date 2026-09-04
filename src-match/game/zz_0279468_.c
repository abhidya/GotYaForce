/* MATCHED  zz_0279468_ @ 0x80279468  (4 instructions)
 *
 *   80279468  28030000  cmplwi r3, 0
 *   8027946c  4d820020  beqlr
 *   80279470  b08300a0  sth r4, 0xa0(r3)
 *   80279474  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr sth blr
 *   exact_bytes      : true
 *   source sha256    : c9abcd60384eda96e6d897d2ccfa7b9ac241d267bef15bfa4691950113c4017b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xa0];
    short          field_a0;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_a0 = p1;
}
