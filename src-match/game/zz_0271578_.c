/* MATCHED  zz_0271578_ @ 0x80271578  (8 instructions)
 *
 *   80271578  9421fff0  stwu r1, -0x10(r1)
 *   8027157c  7c0802a6  mflr r0
 *   80271580  90010014  stw r0, 0x14(r1)
 *   80271584  480096c5  bl 0x8027ac48
 *   80271588  80010014  lwz r0, 0x14(r1)
 *   8027158c  7c0803a6  mtlr r0
 *   80271590  38210010  addi r1, r1, 0x10
 *   80271594  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 84f07838a16682dc0c8916057502b4891436ca64e0867c80ccd9ef9edaee85b0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027ac48_(void);

void f(void)
{
    zz_027ac48_();
}
