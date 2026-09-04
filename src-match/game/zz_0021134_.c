/* MATCHED  zz_0021134_ @ 0x80021134  (5 instructions)
 *
 *   80021134  38800005  li r4, 5
 *   80021138  38000000  li r0, 0
 *   8002113c  988302e4  stb r4, 0x2e4(r3)
 *   80021140  980302e5  stb r0, 0x2e5(r3)
 *   80021144  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li li stb stb blr
 *   exact_bytes      : true
 *   source sha256    : 79fd3afa86f0d960051f005fdcaba28f9c58e3f10e20c6152ef4a2b3ee705e04
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
    p0->field_2e4 = 5;
    p0->field_2e5 = 0;
}
