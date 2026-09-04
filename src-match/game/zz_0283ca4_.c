/* MATCHED  zz_0283ca4_ @ 0x80283ca4  (5 instructions)
 *
 *   80283ca4  80030088  lwz r0, 0x88(r3)
 *   80283ca8  90040000  stw r0, 0(r4)
 *   80283cac  8003008c  lwz r0, 0x8c(r3)
 *   80283cb0  90050000  stw r0, 0(r5)
 *   80283cb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw lwz stw blr
 *   exact_bytes      : true
 *   source sha256    : e1dca3b74a2aeb969042dd428f8c24898748871a942530ffa90456f7812f49a4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x88];
    int            field_88;
    int            field_8c;
} S0;

typedef struct S1 {
    int            field_0;
} S1;

typedef struct S2 {
    int            field_0;
} S2;

void f(S0 *p0, S1 *p1, S2 *p2)
{
    p1->field_0 = p0->field_88;
    p2->field_0 = p0->field_8c;
}
