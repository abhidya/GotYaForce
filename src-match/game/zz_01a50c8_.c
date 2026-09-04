/* MATCHED  zz_01a50c8_ @ 0x801a50c8  (4 instructions)
 *
 *   801a50c8  88830018  lbz r4, 0x18(r3)
 *   801a50cc  38040001  addi r0, r4, 1
 *   801a50d0  98030018  stb r0, 0x18(r3)
 *   801a50d4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : lbz addi stb blr
 *   exact_bytes      : true
 *   source sha256    : 64244b29f2f8153e1831d048df05ace3ab13c2d725084caf0348aa03a5a867fb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x18];
    unsigned char                 field_18;
} S0;

void f(S0 *p0)
{
    p0->field_18 = p0->field_18 + 1;
}
