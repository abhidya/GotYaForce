/* MATCHED  zz_02711e4_ @ 0x802711e4  (8 instructions)
 *
 *   802711e4  9421fff0  stwu r1, -0x10(r1)
 *   802711e8  7c0802a6  mflr r0
 *   802711ec  90010014  stw r0, 0x14(r1)
 *   802711f0  480076c5  bl 0x802788b4
 *   802711f4  80010014  lwz r0, 0x14(r1)
 *   802711f8  7c0803a6  mtlr r0
 *   802711fc  38210010  addi r1, r1, 0x10
 *   80271200  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d726364825bdb400eb4274be0d7ad900e43dfb7462f89845a1c702147d450e1a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02788b4_(void);

void f(void)
{
    zz_02788b4_();
}
