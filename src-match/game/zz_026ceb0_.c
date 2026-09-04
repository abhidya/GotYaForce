/* MATCHED  zz_026ceb0_ @ 0x8026ceb0  (2 instructions)
 *
 *   8026ceb0  98830040  stb r4, 0x40(r3)
 *   8026ceb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stb blr
 *   exact_bytes      : true
 *   source sha256    : 474b9f58a6d6481d14845c3bbefef8d873ef396f7aacedc94e86ebae39ab914d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x40];
    char           field_40;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_40 = p1;
}
