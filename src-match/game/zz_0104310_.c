/* MATCHED  zz_0104310_ @ 0x80104310  (4 instructions)
 *
 *   80104310  a8830072  lha r4, 0x72(r3)
 *   80104314  3804f800  addi r0, r4, -0x800
 *   80104318  b0030072  sth r0, 0x72(r3)
 *   8010431c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha addi sth blr
 *   exact_bytes      : true
 *   source sha256    : f8bc6d736460bd15e742cb85b20562807a8f4294a98979cb61129b452234c911
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x72];
    short                field_72;
} S0;

void f(S0 *p0)
{
    p0->field_72 = p0->field_72 + -2048;
}
