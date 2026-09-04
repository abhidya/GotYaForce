/* MATCHED  zz_0279488_ @ 0x80279488  (4 instructions)
 *
 *   80279488  28030000  cmplwi r3, 0
 *   8027948c  4d820020  beqlr
 *   80279490  90830080  stw r4, 0x80(r3)
 *   80279494  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr stw blr
 *   exact_bytes      : true
 *   source sha256    : d70758d587e406c5e335f6dd39a0252a223f47c70a9051a6db6227f9199a3727
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x80];
    int            field_80;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_80 = p1;
}
