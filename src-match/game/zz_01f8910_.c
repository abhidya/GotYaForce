/* MATCHED  zz_01f8910_ @ 0x801f8910  (10 instructions)
 *
 *   801f8910  9421fff0  stwu r1, -0x10(r1)
 *   801f8914  7c0802a6  mflr r0
 *   801f8918  38600010  li r3, 0x10
 *   801f891c  90010014  stw r0, 0x14(r1)
 *   801f8920  4be90f79  bl 0x80089898
 *   801f8924  4be90c31  bl 0x80089554
 *   801f8928  80010014  lwz r0, 0x14(r1)
 *   801f892c  7c0803a6  mtlr r0
 *   801f8930  38210010  addi r1, r1, 0x10
 *   801f8934  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7d59c4a2f18c0ff352efa83960aa24ef56f032c48fe35458f7696f473a3f93ff
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089554_(void);
extern int zz_0089898_(int);

int f(void)
{
    zz_0089898_(0x10);
    return zz_0089554_();
}
