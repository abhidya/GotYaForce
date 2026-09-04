/* MATCHED  zz_01b41e8_ @ 0x801b41e8  (8 instructions)
 *
 *   801b41e8  9421fff0  stwu r1, -0x10(r1)
 *   801b41ec  7c0802a6  mflr r0
 *   801b41f0  90010014  stw r0, 0x14(r1)
 *   801b41f4  4bfffdd9  bl 0x801b3fcc
 *   801b41f8  80010014  lwz r0, 0x14(r1)
 *   801b41fc  7c0803a6  mtlr r0
 *   801b4200  38210010  addi r1, r1, 0x10
 *   801b4204  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 6d26615027f47b418902dc3110752679ad6dda6996c4795c530b42c29273652a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01b3fcc_(void);

void f(void)
{
    zz_01b3fcc_();
}
