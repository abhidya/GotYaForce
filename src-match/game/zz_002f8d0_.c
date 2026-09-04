/* MATCHED  zz_002f8d0_ @ 0x8002f8d0  (3 instructions)
 *
 *   8002f8d0  38000001  li r0, 1
 *   8002f8d4  90050000  stw r0, 0(r5)
 *   8002f8d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : true
 *   source sha256    : b73804931bc6c9b6da6a61bb7b2b91ea90c65824992fcac87add7d3da0dc76de
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S2 {
    int            field_0;
} S2;

void f(int p0, int p1, S2 *p2)
{
    p2->field_0 = 1;
}
