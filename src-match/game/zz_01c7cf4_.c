/* MATCHED  zz_01c7cf4_ @ 0x801c7cf4  (31 instructions)
 *
 *   801c7cf4  9421fff0  stwu r1, -0x10(r1)
 *   801c7cf8  7c0802a6  mflr r0
 *   801c7cfc  90010014  stw r0, 0x14(r1)
 *   801c7d00  4bec246d  bl 0x8008a16c
 *   801c7d04  4be8bc25  bl 0x80053928
 *   801c7d08  38600028  li r3, 0x28
 *   801c7d0c  4bec1fc5  bl 0x80089cd0
 *   801c7d10  38600020  li r3, 0x20
 *   801c7d14  4bec1fbd  bl 0x80089cd0
 *   801c7d18  38600000  li r3, 0
 *   801c7d1c  4bec1fb5  bl 0x80089cd0
 *   801c7d20  38600010  li r3, 0x10
 *   801c7d24  4bec1fad  bl 0x80089cd0
 *   801c7d28  38600008  li r3, 8
 *   801c7d2c  4bec1fa5  bl 0x80089cd0
 *   801c7d30  38600018  li r3, 0x18
 *   801c7d34  4bec1f9d  bl 0x80089cd0
 *   801c7d38  4bebfadd  bl 0x80087814
 *   801c7d3c  3c608009  lis r3, -0x7ff7
 *   801c7d40  38639eb4  addi r3, r3, -0x614c
 *   801c7d44  4bec4399  bl 0x8008c0dc
 *   801c7d48  3c608009  lis r3, -0x7ff7
 *   801c7d4c  3863a010  addi r3, r3, -0x5ff0
 *   801c7d50  4bec438d  bl 0x8008c0dc
 *   801c7d54  3c608009  lis r3, -0x7ff7
 *   801c7d58  3863a0a8  addi r3, r3, -0x5f58
 *   801c7d5c  4bec4381  bl 0x8008c0dc
 *   801c7d60  80010014  lwz r0, 0x14(r1)
 *   801c7d64  7c0803a6  mtlr r0
 *   801c7d68  38210010  addi r1, r1, 0x10
 *   801c7d6c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl li bl li bl li bl li bl li bl li bl bl lis addi bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4d239261241c344c347d73b5172a88f35eada481766554e50604a7f10fee122a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80089eb4;
extern struct { int v; char pad_[8]; } DAT_8008a010;
extern struct { int v; char pad_[8]; } DAT_8008a0a8;

extern int zz_0053928_(void);
extern int zz_0087814_(void);
extern int zz_0089cd0_(int);
extern int zz_008a16c_(void);
extern int zz_008c0dc_(int);

int f(void)
{
    zz_008a16c_();
    zz_0053928_();
    zz_0089cd0_(0x28);
    zz_0089cd0_(0x20);
    zz_0089cd0_(0);
    zz_0089cd0_(0x10);
    zz_0089cd0_(8);
    zz_0089cd0_(0x18);
    zz_0087814_();
    zz_008c0dc_(&DAT_80089eb4);
    zz_008c0dc_(&DAT_8008a010);
    return zz_008c0dc_(&DAT_8008a0a8);
}
