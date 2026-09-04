/* MATCHED  zz_01a0414_ @ 0x801a0414  (8 instructions)
 *
 *   801a0414  9421fff0  stwu r1, -0x10(r1)
 *   801a0418  7c0802a6  mflr r0
 *   801a041c  90010014  stw r0, 0x14(r1)
 *   801a0420  48000015  bl 0x801a0434
 *   801a0424  80010014  lwz r0, 0x14(r1)
 *   801a0428  7c0803a6  mtlr r0
 *   801a042c  38210010  addi r1, r1, 0x10
 *   801a0430  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0309af2b23450de8b28d4b3fc419af5d131b59ee1878454d35437b2b52cebf7d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_01a0434_(void);

void f(void)
{
    zz_01a0434_();
}
