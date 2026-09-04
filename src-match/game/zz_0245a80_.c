/* MATCHED  zz_0245a80_ @ 0x80245a80  (3 instructions)
 *
 *   80245a80  80030010  lwz r0, 0x10(r3)
 *   80245a84  90040000  stw r0, 0(r4)
 *   80245a88  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw blr
 *   exact_bytes      : true
 *   source sha256    : f16eb0fb8cebfac1e8c8c642ef24360ec9e0560f618dea0a229f7f3f78356c2b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x10];
    int            field_10;
} S0;

typedef struct S1 {
    int            field_0;
} S1;

void f(S0 *p0, S1 *p1)
{
    p1->field_0 = p0->field_10;
}
