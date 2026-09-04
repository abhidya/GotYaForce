/* MATCHED  zz_02af660_ @ 0x802af660  (2 instructions)
 *
 *   802af660  90830064  stw r4, 0x64(r3)
 *   802af664  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 31a9e24d07f7efd02784c2531ac70441852941a189724b05b4bfcfb36dc2e970
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x64];
    int            field_64;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_64 = p1;
}
