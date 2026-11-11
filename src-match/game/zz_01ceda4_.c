/* MATCHED  zz_01ceda4_ @ 0x801ceda4  (22 instructions)
 *
 *   801ceda4  9421fff0  stwu r1, -0x10(r1)
 *   801ceda8  7c0802a6  mflr r0
 *   801cedac  90010014  stw r0, 0x14(r1)
 *   801cedb0  4bebb3bd  bl 0x8008a16c
 *   801cedb4  4be84b75  bl 0x80053928
 *   801cedb8  38600001  li r3, 1
 *   801cedbc  4bebae45  bl 0x80089c00
 *   801cedc0  38600028  li r3, 0x28
 *   801cedc4  4bebae3d  bl 0x80089c00
 *   801cedc8  3c608009  lis r3, -0x7ff7
 *   801cedcc  38639eb4  addi r3, r3, -0x614c
 *   801cedd0  4bebd30d  bl 0x8008c0dc
 *   801cedd4  3c608009  lis r3, -0x7ff7
 *   801cedd8  3863a010  addi r3, r3, -0x5ff0
 *   801ceddc  4bebd301  bl 0x8008c0dc
 *   801cede0  3c608009  lis r3, -0x7ff7
 *   801cede4  3863a0a8  addi r3, r3, -0x5f58
 *   801cede8  4bebd2f5  bl 0x8008c0dc
 *   801cedec  80010014  lwz r0, 0x14(r1)
 *   801cedf0  7c0803a6  mtlr r0
 *   801cedf4  38210010  addi r1, r1, 0x10
 *   801cedf8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl li bl li bl lis addi bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : ed5bd9e09f4cc53342bc5e6a7d9159b5b30bb9fc19f798a96e6c6af780a7dc60
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80089eb4;
extern struct { int v; char pad_[8]; } DAT_8008a010;
extern struct { int v; char pad_[8]; } DAT_8008a0a8;

extern int zz_0053928_(void);
extern int zz_0089c00_(int);
extern int zz_008a16c_(void);
extern int zz_008c0dc_(int);

int f(void)
{
    zz_008a16c_();
    zz_0053928_();
    zz_0089c00_(1);
    zz_0089c00_(0x28);
    zz_008c0dc_(&DAT_80089eb4);
    zz_008c0dc_(&DAT_8008a010);
    return zz_008c0dc_(&DAT_8008a0a8);
}
