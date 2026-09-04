/* MATCHED  zz_0276e24_ @ 0x80276e24  (2 instructions)
 *
 *   80276e24  8063001c  lwz r3, 0x1c(r3)
 *   80276e28  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : ea399b54f7ef46ce60f94ce87562f7aefad0a065bd2817429a5be82dca0771ae
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x1c];
    int            field_1c;
} S0;

int f(S0 *p0)
{
    return p0->field_1c;
}
