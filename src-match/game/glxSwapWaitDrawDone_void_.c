/* MATCHED  glxSwapWaitDrawDone(void) @ 0x80181db0  (10 instructions)
 *
 *   80181db0  9421fff0  stwu r1, -0x10(r1)
 *   80181db4  7c0802a6  mflr r0
 *   80181db8  90010014  stw r0, 0x14(r1)
 *   80181dbc  48015b15  bl 0x801978d0
 *   80181dc0  4be86d99  bl 0x80008b58
 *   80181dc4  4be8817d  bl 0x80009f40
 *   80181dc8  80010014  lwz r0, 0x14(r1)
 *   80181dcc  7c0803a6  mtlr r0
 *   80181dd0  38210010  addi r1, r1, 0x10
 *   80181dd4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1b27a3c1d01cc57831601820c5dca5dfe2eac0061fdb1b5584b5474d70ae500a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0008b58_(void);
extern int zz_0009f40_(void);
extern int zz_01978d0_(void);

int f(void)
{
    zz_01978d0_();
    zz_0008b58_();
    return zz_0009f40_();
}
