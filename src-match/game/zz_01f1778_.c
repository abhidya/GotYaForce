/* MATCHED  zz_01f1778_ @ 0x801f1778  (9 instructions)
 *
 *   801f1778  9421fff0  stwu r1, -0x10(r1)
 *   801f177c  7c0802a6  mflr r0
 *   801f1780  90010014  stw r0, 0x14(r1)
 *   801f1784  48000019  bl 0x801f179c
 *   801f1788  48000041  bl 0x801f17c8
 *   801f178c  80010014  lwz r0, 0x14(r1)
 *   801f1790  7c0803a6  mtlr r0
 *   801f1794  38210010  addi r1, r1, 0x10
 *   801f1798  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ccd766ec1cfbf04b55777db8f8b4a322f393a07f96ff2233215a1a409bceebfb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01f179c_(void);
extern int zz_01f17c8_(void);

int f(void)
{
    zz_01f179c_();
    return zz_01f17c8_();
}
