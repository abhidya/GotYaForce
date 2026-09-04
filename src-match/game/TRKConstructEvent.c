/* MATCHED  TRKConstructEvent @ 0x8022cc24  (6 instructions)
 *
 *   8022cc24  90830000  stw r4, 0(r3)
 *   8022cc28  38800000  li r4, 0
 *   8022cc2c  3800ffff  li r0, -1
 *   8022cc30  90830004  stw r4, 4(r3)
 *   8022cc34  90030008  stw r0, 8(r3)
 *   8022cc38  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw li li stw stw blr
 *   exact_bytes      : true
 *   source sha256    : bf0ff601660dc3a440f5b2ea28f26eadbae43ed1bb4c28ad9e6c36de4e5c042a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int            field_0;
    int            field_4;
    int            field_8;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_0 = p1;
    p0->field_4 = 0;
    p0->field_8 = -1;
}
