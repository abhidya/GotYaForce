/* MATCHED  zz_027094c_ @ 0x8027094c  (2 instructions)
 *
 *   8027094c  8063000c  lwz r3, 0xc(r3)
 *   80270950  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : a5f3b501f5695b4620cb4bb09f31368672f48ef0ace44cba8ee4face1a81c7b6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int            field_c;
} S0;

int f(S0 *p0)
{
    return p0->field_c;
}
