/* MATCHED  zz_0268204_ @ 0x80268204  (2 instructions)
 *
 *   80268204  80630090  lwz r3, 0x90(r3)
 *   80268208  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : bff9d800bf4270976577ca77b40657e788e8c58cc4efad284ae2d271eb860ca5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x90];
    int            field_90;
} S0;

int f(S0 *p0)
{
    return p0->field_90;
}
