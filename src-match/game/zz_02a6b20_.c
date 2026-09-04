/* MATCHED  zz_02a6b20_ @ 0x802a6b20  (2 instructions)
 *
 *   802a6b20  90830008  stw r4, 8(r3)
 *   802a6b24  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : b1c43feceecf88344bf716910b3f1c8591a09225a514727000258461326b41a9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int            field_8;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_8 = p1;
}
