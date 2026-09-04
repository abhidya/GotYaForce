/* MATCHED  zz_026831c_ @ 0x8026831c  (2 instructions)
 *
 *   8026831c  80630004  lwz r3, 4(r3)
 *   80268320  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : aabcf1202bbdba15bd12bca033ad7b85392b3e0db6b24b9f969f979a8fa3395a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int            field_4;
} S0;

int f(S0 *p0)
{
    return p0->field_4;
}
