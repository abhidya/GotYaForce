/* MATCHED  zz_0271414_ @ 0x80271414  (8 instructions)
 *
 *   80271414  9421fff0  stwu r1, -0x10(r1)
 *   80271418  7c0802a6  mflr r0
 *   8027141c  90010014  stw r0, 0x14(r1)
 *   80271420  4800812d  bl 0x8027954c
 *   80271424  80010014  lwz r0, 0x14(r1)
 *   80271428  7c0803a6  mtlr r0
 *   8027142c  38210010  addi r1, r1, 0x10
 *   80271430  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 85aedad018aaf1a1672c1779214b5b902555cf8c37142772260614793f19b170
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_027954c_(void);

void f(void)
{
    zz_027954c_();
}
