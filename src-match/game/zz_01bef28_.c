/* MATCHED  zz_01bef28_ @ 0x801bef28  (18 instructions)
 *
 *   801bef28  9421fff0  stwu r1, -0x10(r1)
 *   801bef2c  7c0802a6  mflr r0
 *   801bef30  90010014  stw r0, 0x14(r1)
 *   801bef34  4becb239  bl 0x8008a16c
 *   801bef38  38600010  li r3, 0x10
 *   801bef3c  4becacc5  bl 0x80089c00
 *   801bef40  38600039  li r3, 0x39
 *   801bef44  4becacbd  bl 0x80089c00
 *   801bef48  3c608009  lis r3, -0x7ff7
 *   801bef4c  38639eb4  addi r3, r3, -0x614c
 *   801bef50  4becd18d  bl 0x8008c0dc
 *   801bef54  3c608009  lis r3, -0x7ff7
 *   801bef58  38639f28  addi r3, r3, -0x60d8
 *   801bef5c  4becd1a9  bl 0x8008c104
 *   801bef60  80010014  lwz r0, 0x14(r1)
 *   801bef64  7c0803a6  mtlr r0
 *   801bef68  38210010  addi r1, r1, 0x10
 *   801bef6c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl li bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e753e323f6a8ec73567b90444ac04ef304f6bcf6ddbe7179355000924e1a453c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80089eb4;
extern struct { int v; char pad_[8]; } DAT_80089f28;

extern int zz_0089c00_(int);
extern int zz_008a16c_(void);
extern int zz_008c0dc_(int);
extern int zz_008c104_(int);

int f(void)
{
    zz_008a16c_();
    zz_0089c00_(0x10);
    zz_0089c00_(0x39);
    zz_008c0dc_(&DAT_80089eb4);
    return zz_008c104_(&DAT_80089f28);
}
