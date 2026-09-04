/* MATCHED  zz_01beec0_ @ 0x801beec0  (9 instructions)
 *
 *   801beec0  9421fff0  stwu r1, -0x10(r1)
 *   801beec4  7c0802a6  mflr r0
 *   801beec8  90010014  stw r0, 0x14(r1)
 *   801beecc  48000019  bl 0x801beee4
 *   801beed0  48000059  bl 0x801bef28
 *   801beed4  80010014  lwz r0, 0x14(r1)
 *   801beed8  7c0803a6  mtlr r0
 *   801beedc  38210010  addi r1, r1, 0x10
 *   801beee0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4d7cb41874dc14c689ffb34b6444ac4763d938f813d444cf6206fa0f3638c22a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01beee4_(void);
extern int zz_01bef28_(void);

int f(void)
{
    zz_01beee4_();
    return zz_01bef28_();
}
