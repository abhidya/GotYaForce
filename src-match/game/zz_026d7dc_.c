/* MATCHED  zz_026d7dc_ @ 0x8026d7dc  (3 instructions)
 *
 *   8026d7dc  88630001  lbz r3, 1(r3)
 *   8026d7e0  7c630774  extsb r3, r3
 *   8026d7e4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lbz extsb blr
 *   exact_bytes      : true
 *   source sha256    : eb151a1bab2c860651383b6373141c4e55f2736760180dbe33e9372560bb3fc2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x1];
    char           field_1;
} S0;

int f(S0 *p0)
{
    return p0->field_1;
}
