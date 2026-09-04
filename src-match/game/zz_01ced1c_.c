/* MATCHED  zz_01ced1c_ @ 0x801ced1c  (9 instructions)
 *
 *   801ced1c  9421fff0  stwu r1, -0x10(r1)
 *   801ced20  7c0802a6  mflr r0
 *   801ced24  90010014  stw r0, 0x14(r1)
 *   801ced28  48000019  bl 0x801ced40
 *   801ced2c  48000079  bl 0x801ceda4
 *   801ced30  80010014  lwz r0, 0x14(r1)
 *   801ced34  7c0803a6  mtlr r0
 *   801ced38  38210010  addi r1, r1, 0x10
 *   801ced3c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ffc56d7d9d08cedc1d044097680dc338beab135506620c5fda22732338d952c3
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01ced40_(void);
extern int zz_01ceda4_(void);

int f(void)
{
    zz_01ced40_();
    return zz_01ceda4_();
}
