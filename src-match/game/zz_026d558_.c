/* MATCHED  zz_026d558_ @ 0x8026d558  (3 instructions)
 *
 *   8026d558  90830034  stw r4, 0x34(r3)
 *   8026d55c  90a30038  stw r5, 0x38(r3)
 *   8026d560  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 36140952606019f678d4048b6a24a79e77e389a92ad4d386a2ea2a68724178db
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x34];
    int            field_34;
    int            field_38;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_34 = p1;
    p0->field_38 = p2;
}
