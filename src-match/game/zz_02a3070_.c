/* MATCHED  zz_02a3070_ @ 0x802a3070  (7 instructions)
 *
 *   802a3070  38000000  li r0, 0
 *   802a3074  90030000  stw r0, 0(r3)
 *   802a3078  90030004  stw r0, 4(r3)
 *   802a307c  90030008  stw r0, 8(r3)
 *   802a3080  9003000c  stw r0, 0xc(r3)
 *   802a3084  90030010  stw r0, 0x10(r3)
 *   802a3088  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw stw stw blr
 *   exact_bytes      : true
 *   source sha256    : b86e5b462eae40c3c55ae61d165c65643f810bc0d980eaf2b0538f09553a6ef2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
    int            field_4;
    int            field_8;
    int            field_c;
    int            field_10;
} S0;

void f(S0 *p0)
{
    p0->field_0 = 0;
    p0->field_4 = 0;
    p0->field_8 = 0;
    p0->field_c = 0;
    p0->field_10 = 0;
}
