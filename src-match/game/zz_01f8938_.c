/* MATCHED  zz_01f8938_ @ 0x801f8938  (13 instructions)
 *
 *   801f8938  9421fff0  stwu r1, -0x10(r1)
 *   801f893c  7c0802a6  mflr r0
 *   801f8940  90010014  stw r0, 0x14(r1)
 *   801f8944  4be91829  bl 0x8008a16c
 *   801f8948  38600010  li r3, 0x10
 *   801f894c  4be912b5  bl 0x80089c00
 *   801f8950  3c608009  lis r3, -0x7ff7
 *   801f8954  38639eb4  addi r3, r3, -0x614c
 *   801f8958  4be93785  bl 0x8008c0dc
 *   801f895c  80010014  lwz r0, 0x14(r1)
 *   801f8960  7c0803a6  mtlr r0
 *   801f8964  38210010  addi r1, r1, 0x10
 *   801f8968  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 25f0b44cce7fe963f9da777fe45775da99ef5e02b19114d78d8234281fe6b300
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80089eb4;

extern int zz_0089c00_(int);
extern int zz_008a16c_(void);
extern int zz_008c0dc_(int);

int f(void)
{
    zz_008a16c_();
    zz_0089c00_(0x10);
    return zz_008c0dc_(&DAT_80089eb4);
}
