/* MATCHED  zz_01f6a88_ @ 0x801f6a88  (4 instructions)
 *
 *   801f6a88  88830150  lbz r4, 0x150(r3)
 *   801f6a8c  3804ffff  addi r0, r4, -1
 *   801f6a90  98030150  stb r0, 0x150(r3)
 *   801f6a94  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (1 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 1
 *   shape            : lbz addi stb blr
 *   exact_bytes      : true
 *   source sha256    : b4bd1c85f22caa5a25df795bb9e75bde025d47fc6939fe26f5d05b418cb1cd6b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x150];
    unsigned char                 field_150;
} S0;

void f(S0 *p0)
{
    p0->field_150 = p0->field_150 + -1;
}
