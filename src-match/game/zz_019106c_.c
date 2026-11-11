/* MATCHED  zz_019106c_ @ 0x8019106c  (18 instructions)
 *
 *   8019106c  9421fff0  stwu r1, -0x10(r1)
 *   80191070  7c0802a6  mflr r0
 *   80191074  90010014  stw r0, 0x14(r1)
 *   80191078  4bef90f5  bl 0x8008a16c
 *   8019107c  38600010  li r3, 0x10
 *   80191080  4bef8b81  bl 0x80089c00
 *   80191084  38600038  li r3, 0x38
 *   80191088  4bef8b79  bl 0x80089c00
 *   8019108c  3c608009  lis r3, -0x7ff7
 *   80191090  38639eb4  addi r3, r3, -0x614c
 *   80191094  4befb049  bl 0x8008c0dc
 *   80191098  3c608009  lis r3, -0x7ff7
 *   8019109c  38639f28  addi r3, r3, -0x60d8
 *   801910a0  4befb065  bl 0x8008c104
 *   801910a4  80010014  lwz r0, 0x14(r1)
 *   801910a8  7c0803a6  mtlr r0
 *   801910ac  38210010  addi r1, r1, 0x10
 *   801910b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl li bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d17534ec50d8f50536af0b6c32bc4a51c935cf6a4a44daed31635fef49f67cdf
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
    zz_0089c00_(0x38);
    zz_008c0dc_(&DAT_80089eb4);
    return zz_008c104_(&DAT_80089f28);
}
