/* MATCHED  zz_027098c_ @ 0x8027098c  (7 instructions)
 *
 *   8027098c  a8030034  lha r0, 0x34(r3)
 *   80270990  b0040000  sth r0, 0(r4)
 *   80270994  a8030036  lha r0, 0x36(r3)
 *   80270998  b0050000  sth r0, 0(r5)
 *   8027099c  a8030038  lha r0, 0x38(r3)
 *   802709a0  b0060000  sth r0, 0(r6)
 *   802709a4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha sth lha sth lha sth blr
 *   exact_bytes      : true
 *   source sha256    : 83e503d0fd7330024352efbb4b62ea576f0cf906d413b2e9b84525842e9c68e3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x34];
    short          field_34;
    short          field_36;
    short          field_38;
} S0;

typedef struct S1 {
    short          field_0;
} S1;

typedef struct S2 {
    short          field_0;
} S2;

typedef struct S3 {
    short          field_0;
} S3;

void f(S0 *p0, S1 *p1, S2 *p2, S3 *p3)
{
    p1->field_0 = p0->field_34;
    p2->field_0 = p0->field_36;
    p3->field_0 = p0->field_38;
}
