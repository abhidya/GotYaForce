/* MATCHED  zz_01b419c_ @ 0x801b419c  (8 instructions)
 *
 *   801b419c  9421fff0  stwu r1, -0x10(r1)
 *   801b41a0  7c0802a6  mflr r0
 *   801b41a4  90010014  stw r0, 0x14(r1)
 *   801b41a8  4bfffc95  bl 0x801b3e3c
 *   801b41ac  80010014  lwz r0, 0x14(r1)
 *   801b41b0  7c0803a6  mtlr r0
 *   801b41b4  38210010  addi r1, r1, 0x10
 *   801b41b8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 11041b88d308b8b35e1b45acbfc4861ef641555c66e75f12a7ff370b1f838451
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01b3e3c_(void);

void f(void)
{
    zz_01b3e3c_();
}
