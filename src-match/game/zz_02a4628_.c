/* MATCHED  zz_02a4628_ @ 0x802a4628  (8 instructions)
 *
 *   802a4628  9421fff0  stwu r1, -0x10(r1)
 *   802a462c  7c0802a6  mflr r0
 *   802a4630  90010014  stw r0, 0x14(r1)
 *   802a4634  48004d45  bl 0x802a9378
 *   802a4638  80010014  lwz r0, 0x14(r1)
 *   802a463c  7c0803a6  mtlr r0
 *   802a4640  38210010  addi r1, r1, 0x10
 *   802a4644  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4c1578ab9e2badc3e2a3e5bbbb7f9f892523c5a92f11f44c5ea322363ac90124
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_02a9378_(void);

void f(void)
{
    zz_02a9378_();
}
