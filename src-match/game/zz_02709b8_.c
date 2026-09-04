/* MATCHED  zz_02709b8_ @ 0x802709b8  (9 instructions)
 *
 *   802709b8  a8030028  lha r0, 0x28(r3)
 *   802709bc  b0040000  sth r0, 0(r4)
 *   802709c0  a803002a  lha r0, 0x2a(r3)
 *   802709c4  b0050000  sth r0, 0(r5)
 *   802709c8  a803002c  lha r0, 0x2c(r3)
 *   802709cc  b0040002  sth r0, 2(r4)
 *   802709d0  a803002e  lha r0, 0x2e(r3)
 *   802709d4  b0050002  sth r0, 2(r5)
 *   802709d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha sth lha sth lha sth lha sth blr
 *   exact_bytes      : true
 *   source sha256    : 0bbc05d6be2d3a662a69aaa5948a8181af4ebdded35a4172f10ac586a2a46841
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
    p1->field_0 = p0->field_28;
    p2->field_0 = p0->field_2a;
    p1->field_2 = p0->field_2c;
    p2->field_2 = p0->field_2e;
}
