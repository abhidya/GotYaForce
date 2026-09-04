/* MATCHED  zz_026cec0_ @ 0x8026cec0  (3 instructions)
 *
 *   8026cec0  90830028  stw r4, 0x28(r3)
 *   8026cec4  38600001  li r3, 1
 *   8026cec8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw li blr
 *   exact_bytes      : true
 *   source sha256    : a41b1b6fedc643bdb5e86ba1045abc6f4383293e38ce4e20a256f90f6487d4a8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x28];
    int            field_28;
} S0;

int f(S0 *p0, int p1)
{
    p0->field_28 = p1;
    return 1;
}
