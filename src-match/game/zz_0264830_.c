/* MATCHED  zz_0264830_ @ 0x80264830  (2 instructions)
 *
 *   80264830  90830034  stw r4, 0x34(r3)
 *   80264834  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 456c7b321f5f6debc89d354db67e534a1a0fa67969b06cd88ebb098117dc19fe
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x34];
    int            field_34;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_34 = p1;
}
