/* MATCHED  zz_0271454_ @ 0x80271454  (8 instructions)
 *
 *   80271454  9421fff0  stwu r1, -0x10(r1)
 *   80271458  7c0802a6  mflr r0
 *   8027145c  90010014  stw r0, 0x14(r1)
 *   80271460  480082ed  bl 0x8027974c
 *   80271464  80010014  lwz r0, 0x14(r1)
 *   80271468  7c0803a6  mtlr r0
 *   8027146c  38210010  addi r1, r1, 0x10
 *   80271470  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 8b52621a3e8d5286bd37285a6c2a38be79484832644484b50ba6bb18977d6ef8
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027974c_(void);

void f(void)
{
    zz_027974c_();
}
