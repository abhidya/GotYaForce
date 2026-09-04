/* MATCHED  zz_0046ef4_ @ 0x80046ef4  (5 instructions)
 *
 *   80046ef4  c0231d60  lfs f1, 0x1d60(r3)
 *   80046ef8  c002867c  lfs f0, -0x7984(r2)
 *   80046efc  ec010032  fmuls f0, f1, f0
 *   80046f00  d0031d60  stfs f0, 0x1d60(r3)
 *   80046f04  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lfs lfs fmuls stfs blr
 *   exact_bytes      : false
 *   source sha256    : 96115da48cdb47d6f635bd8e91657b258887f02b8e70ca8b8e0f0a9cd493ae55
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x1d60];
    float                field_1d60;
} S0;

extern float FLOAT_8043709c;

void f(S0 *p0)
{
    p0->field_1d60 = p0->field_1d60 * FLOAT_8043709c;
}
