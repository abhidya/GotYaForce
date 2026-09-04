/* MATCHED  zz_026cecc_ @ 0x8026cecc  (4 instructions)
 *
 *   8026cecc  90830018  stw r4, 0x18(r3)
 *   8026ced0  90a30014  stw r5, 0x14(r3)
 *   8026ced4  38600001  li r3, 1
 *   8026ced8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw li blr
 *   exact_bytes      : true
 *   source sha256    : 0728a22c81ffb39b983f8c2f86cc99e4886612c8c17089723dac910273f25848
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x14];
    int            field_14;
    int            field_18;
} S0;

int f(S0 *p0, int p1, int p2)
{
    p0->field_18 = p1;
    p0->field_14 = p2;
    return 1;
}
