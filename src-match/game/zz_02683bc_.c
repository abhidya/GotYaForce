/* MATCHED  zz_02683bc_ @ 0x802683bc  (2 instructions)
 *
 *   802683bc  80630034  lwz r3, 0x34(r3)
 *   802683c0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 5b50eecee188838fd224091e4cc2542495ddfd9325c7a25efa76b278b95611da
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x34];
    int            field_34;
} S0;

int f(S0 *p0)
{
    return p0->field_34;
}
