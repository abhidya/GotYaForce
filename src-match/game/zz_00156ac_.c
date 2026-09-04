/* MATCHED  zz_00156ac_ @ 0x800156ac  (8 instructions)
 *
 *   800156ac  9421fff0  stwu r1, -0x10(r1)
 *   800156b0  7c0802a6  mflr r0
 *   800156b4  90010014  stw r0, 0x14(r1)
 *   800156b8  4bfff8d9  bl 0x80014f90
 *   800156bc  80010014  lwz r0, 0x14(r1)
 *   800156c0  7c0803a6  mtlr r0
 *   800156c4  38210010  addi r1, r1, 0x10
 *   800156c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 37f1ee69b8d4aeb5f4ffdd89ddba1a2a834d25eb44c9c7a5de28681f29b77490
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_0014f90_(void);

void f(void)
{
    zz_0014f90_();
}
