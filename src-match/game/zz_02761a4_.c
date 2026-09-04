/* MATCHED  zz_02761a4_ @ 0x802761a4  (2 instructions)
 *
 *   802761a4  90830028  stw r4, 0x28(r3)
 *   802761a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : d18fd06720aac7025190f7bbd47803919a1eabd450f48b8a24a5e7682f3a636b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x28];
    int            field_28;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_28 = p1;
}
