/* MATCHED  zz_021f8e8_ @ 0x8021f8e8  (2 instructions)
 *
 *   8021f8e8  80630088  lwz r3, 0x88(r3)
 *   8021f8ec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 155031f4092b59f82372209659113d2229e0dbefea3ffa9cecf68699f4a1cc01
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x88];
    int            field_88;
} S0;

int f(S0 *p0)
{
    return p0->field_88;
}
