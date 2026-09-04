/* MATCHED  zz_02683e4_ @ 0x802683e4  (2 instructions)
 *
 *   802683e4  80630018  lwz r3, 0x18(r3)
 *   802683e8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 223357b29626f6846a63852f237e929dc42141a9448e44f597ed9d93a62658a5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x18];
    int            field_18;
} S0;

int f(S0 *p0)
{
    return p0->field_18;
}
