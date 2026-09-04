/* MATCHED  zz_02a3cb0_ @ 0x802a3cb0  (2 instructions)
 *
 *   802a3cb0  80630f28  lwz r3, 0xf28(r3)
 *   802a3cb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : a1ac6ad5d3a19296be2c63d00c36f265fc066ed34dda481604a1fe2f1130f46d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xf28];
    int            field_f28;
} S0;

int f(S0 *p0)
{
    return p0->field_f28;
}
