/* MATCHED  zz_026820c_ @ 0x8026820c  (2 instructions)
 *
 *   8026820c  80630094  lwz r3, 0x94(r3)
 *   80268210  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 177e4c6b75bda6ede58d0112880723cfc4c7a4d475cf79e12d6601cbed3ee078
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x94];
    int            field_94;
} S0;

int f(S0 *p0)
{
    return p0->field_94;
}
