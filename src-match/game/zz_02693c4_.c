/* MATCHED  zz_02693c4_ @ 0x802693c4  (2 instructions)
 *
 *   802693c4  90830020  stw r4, 0x20(r3)
 *   802693c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 8de83d184f4677e21c6d836e5104f982b0d18e65083df3baf6b369679f9b421c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x20];
    int            field_20;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_20 = p1;
}
