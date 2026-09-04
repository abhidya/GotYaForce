/* MATCHED  zz_021fcec_ @ 0x8021fcec  (2 instructions)
 *
 *   8021fcec  80630084  lwz r3, 0x84(r3)
 *   8021fcf0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : b24d8a0f401e8036fbe66059d3b2478dcb809f7f3aa9275be007f04a10aa4fba
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x84];
    int            field_84;
} S0;

int f(S0 *p0)
{
    return p0->field_84;
}
