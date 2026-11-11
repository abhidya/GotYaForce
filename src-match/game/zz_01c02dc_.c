/* MATCHED  zz_01c02dc_ @ 0x801c02dc  (8 instructions)
 *
 *   801c02dc  9421fff0  stwu r1, -0x10(r1)
 *   801c02e0  7c0802a6  mflr r0
 *   801c02e4  90010014  stw r0, 0x14(r1)
 *   801c02e8  4bfffa95  bl 0x801bfd7c
 *   801c02ec  80010014  lwz r0, 0x14(r1)
 *   801c02f0  7c0803a6  mtlr r0
 *   801c02f4  38210010  addi r1, r1, 0x10
 *   801c02f8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2968e97a62166191d8947eb2065cbb1a1f1e420daca2d78940cc3f2298965476
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_801bfd7c(void);

void f(void)
{
    FUN_801bfd7c();
}
