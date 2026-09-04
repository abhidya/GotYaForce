/* MATCHED  zz_02709dc_ @ 0x802709dc  (9 instructions)
 *
 *   802709dc  a8040000  lha r0, 0(r4)
 *   802709e0  b0030028  sth r0, 0x28(r3)
 *   802709e4  a8050000  lha r0, 0(r5)
 *   802709e8  b003002a  sth r0, 0x2a(r3)
 *   802709ec  a8040002  lha r0, 2(r4)
 *   802709f0  b003002c  sth r0, 0x2c(r3)
 *   802709f4  a8050002  lha r0, 2(r5)
 *   802709f8  b003002e  sth r0, 0x2e(r3)
 *   802709fc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha sth lha sth lha sth lha sth blr
 *   exact_bytes      : true
 *   source sha256    : d685f15462e7068dacfdf507352d88248c1a3a98ebe81ed224ce4e70bbb156ee
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x28];
    short          field_28;
    short          field_2a;
    short          field_2c;
    short          field_2e;
} S0;

typedef struct S1 {
    short          field_0;
    short          field_2;
} S1;

typedef struct S2 {
    short          field_0;
    short          field_2;
} S2;

void f(S0 *p0, S1 *p1, S2 *p2)
{
    p0->field_28 = p1->field_0;
    p0->field_2a = p2->field_0;
    p0->field_2c = p1->field_2;
    p0->field_2e = p2->field_2;
}
