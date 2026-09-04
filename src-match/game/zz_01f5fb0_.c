/* MATCHED  zz_01f5fb0_ @ 0x801f5fb0  (9 instructions)
 *
 *   801f5fb0  9421fff0  stwu r1, -0x10(r1)
 *   801f5fb4  7c0802a6  mflr r0
 *   801f5fb8  90010014  stw r0, 0x14(r1)
 *   801f5fbc  48000019  bl 0x801f5fd4
 *   801f5fc0  4800003d  bl 0x801f5ffc
 *   801f5fc4  80010014  lwz r0, 0x14(r1)
 *   801f5fc8  7c0803a6  mtlr r0
 *   801f5fcc  38210010  addi r1, r1, 0x10
 *   801f5fd0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a4704a2fd79f888f80bc5e8ddca13351357b5864fb32c9028dc3c8742c0fd1cd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01f5fd4_(void);
extern int zz_01f5ffc_(void);

int f(void)
{
    zz_01f5fd4_();
    return zz_01f5ffc_();
}
