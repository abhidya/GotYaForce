/* MATCHED  zz_01f88ec_ @ 0x801f88ec  (9 instructions)
 *
 *   801f88ec  9421fff0  stwu r1, -0x10(r1)
 *   801f88f0  7c0802a6  mflr r0
 *   801f88f4  90010014  stw r0, 0x14(r1)
 *   801f88f8  48000019  bl 0x801f8910
 *   801f88fc  4800003d  bl 0x801f8938
 *   801f8900  80010014  lwz r0, 0x14(r1)
 *   801f8904  7c0803a6  mtlr r0
 *   801f8908  38210010  addi r1, r1, 0x10
 *   801f890c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5991413c56a9036c433e9f4f806e564faf512aa21c0264fe952bd7f6d42bbbd9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_01f8910_(void);
extern int zz_01f8938_(void);

int f(void)
{
    zz_01f8910_();
    return zz_01f8938_();
}
