/* MATCHED  zz_0009c38_ @ 0x80009c38  (5 instructions)
 *
 *   80009c38  9883001c  stb r4, 0x1c(r3)
 *   80009c3c  98a3001d  stb r5, 0x1d(r3)
 *   80009c40  98c3001e  stb r6, 0x1e(r3)
 *   80009c44  98e3001f  stb r7, 0x1f(r3)
 *   80009c48  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stb stb stb stb blr
 *   exact_bytes      : true
 *   source sha256    : 6c71aec42c9ffb05e8c5a486ce68696860d5993f42368687f264817b650c3394
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x1c];
    char           field_1c;
    char           field_1d;
    char           field_1e;
    char           field_1f;
} S0;

void f(S0 *p0, int p1, int p2, int p3, int p4)
{
    p0->field_1c = p1;
    p0->field_1d = p2;
    p0->field_1e = p3;
    p0->field_1f = p4;
}
