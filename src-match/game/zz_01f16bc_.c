/* MATCHED  zz_01f16bc_ @ 0x801f16bc  (13 instructions)
 *
 *   801f16bc  9421fff0  stwu r1, -0x10(r1)
 *   801f16c0  7c0802a6  mflr r0
 *   801f16c4  3c60803c  lis r3, -0x7fc4
 *   801f16c8  38800000  li r4, 0
 *   801f16cc  90010014  stw r0, 0x14(r1)
 *   801f16d0  386373b0  addi r3, r3, 0x73b0
 *   801f16d4  38a003e4  li r5, 0x3e4
 *   801f16d8  4be13d35  bl 0x8000540c
 *   801f16dc  48000015  bl 0x801f16f0
 *   801f16e0  80010014  lwz r0, 0x14(r1)
 *   801f16e4  7c0803a6  mtlr r0
 *   801f16e8  38210010  addi r1, r1, 0x10
 *   801f16ec  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7cfd91836273905a21f3163eefd5da769949bc7a7914dc09218aa280d16c587e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803c73b0;

extern int FUN_8000540c(int, int, int);
extern int zz_01f16f0_(void);

int f(void)
{
    FUN_8000540c(&DAT_803c73b0, 0, 0x3e4);
    return zz_01f16f0_();
}
