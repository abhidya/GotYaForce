/* MATCHED  zz_02af668_ @ 0x802af668  (2 instructions)
 *
 *   802af668  90830060  stw r4, 0x60(r3)
 *   802af66c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : a1bcd759fbc595566a6260c8ee2ebd318412ca1b712e3d9cfcd8919f4d1036b9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x60];
    int            field_60;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_60 = p1;
}
