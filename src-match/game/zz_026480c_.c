/* MATCHED  zz_026480c_ @ 0x8026480c  (2 instructions)
 *
 *   8026480c  90830044  stw r4, 0x44(r3)
 *   80264810  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : dcdf7c5d51615a0f87bd80845208ef9f229d26c821048fc6b720dce70e7d5ccf
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x44];
    int            field_44;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_44 = p1;
}
