/* MATCHED  zz_02a0a80_ @ 0x802a0a80  (5 instructions)
 *
 *   802a0a80  28030000  cmplwi r3, 0
 *   802a0a84  4d820020  beqlr
 *   802a0a88  38000002  li r0, 2
 *   802a0a8c  90030000  stw r0, 0(r3)
 *   802a0a90  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr li stw blr
 *   exact_bytes      : true
 *   source sha256    : d4d347baf16c3c2f920400b4dcbf203f4996519cbbe391a961d016c73aa9a90a
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
    p0->field_0 = 2;
}
