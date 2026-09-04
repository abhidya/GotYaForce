/* MATCHED  zz_0264824_ @ 0x80264824  (3 instructions)
 *
 *   80264824  90830048  stw r4, 0x48(r3)
 *   80264828  90a3004c  stw r5, 0x4c(r3)
 *   8026482c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 6103078ab1a4e98d716d3489a79b89a096ce2b4c47ddd1e24116cca25991bd0f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x48];
    int            field_48;
    int            field_4c;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_48 = p1;
    p0->field_4c = p2;
}
