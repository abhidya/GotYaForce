/* MATCHED  zz_0264814_ @ 0x80264814  (2 instructions)
 *
 *   80264814  90830040  stw r4, 0x40(r3)
 *   80264818  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : d973aed2f197897f66d7071c5680b4c6c9229dd4065ab78d14dc64d4f73dfa4d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x40];
    int            field_40;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_40 = p1;
}
