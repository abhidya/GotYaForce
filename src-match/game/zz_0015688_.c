/* MATCHED  zz_0015688_ @ 0x80015688  (8 instructions)
 *
 *   80015688  9421fff0  stwu r1, -0x10(r1)
 *   8001568c  7c0802a6  mflr r0
 *   80015690  90010014  stw r0, 0x14(r1)
 *   80015694  4bfff8fd  bl 0x80014f90
 *   80015698  80010014  lwz r0, 0x14(r1)
 *   8001569c  7c0803a6  mtlr r0
 *   800156a0  38210010  addi r1, r1, 0x10
 *   800156a4  4e800020  blr
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
