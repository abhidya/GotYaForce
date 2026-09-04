/* MATCHED  zz_027bbac_ @ 0x8027bbac  (3 instructions)
 *
 *   8027bbac  90830058  stw r4, 0x58(r3)
 *   8027bbb0  90a3005c  stw r5, 0x5c(r3)
 *   8027bbb4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 84d9621f52a9f295cdfe0935f2e02c70d6a65f0736d1ecdcbeecfd1ec7fd877a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x58];
    int            field_58;
    int            field_5c;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_58 = p1;
    p0->field_5c = p2;
}
