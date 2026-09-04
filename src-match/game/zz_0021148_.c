/* MATCHED  zz_0021148_ @ 0x80021148  (5 instructions)
 *
 *   80021148  38800006  li r4, 6
 *   8002114c  38000000  li r0, 0
 *   80021150  988302e4  stb r4, 0x2e4(r3)
 *   80021154  980302e5  stb r0, 0x2e5(r3)
 *   80021158  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li li stb stb blr
 *   exact_bytes      : true
 *   source sha256    : 19f3d12337d2d3bf6e21a3c9a7ecb3a1752804c9ce66c3d14ba398b87acea367
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x2e4];
    char           field_2e4;
    char           field_2e5;
} S0;

void f(S0 *p0)
{
    p0->field_2e4 = 6;
    p0->field_2e5 = 0;
}
