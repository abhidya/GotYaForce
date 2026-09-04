/* MATCHED  zz_02a0a94_ @ 0x802a0a94  (5 instructions)
 *
 *   802a0a94  28030000  cmplwi r3, 0
 *   802a0a98  4d820020  beqlr
 *   802a0a9c  38000000  li r0, 0
 *   802a0aa0  90030000  stw r0, 0(r3)
 *   802a0aa4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr li stw blr
 *   exact_bytes      : true
 *   source sha256    : ec808f0ba27a584aa8d5f2a7c2e997e9946f38a03ad0e240e0fee49a22f92867
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
} S0;

void f(S0 *p0)
{
    if (p0 == 0)
        return;
    p0->field_0 = 0;
}
