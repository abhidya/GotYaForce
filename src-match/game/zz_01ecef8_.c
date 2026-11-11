/* MATCHED  zz_01ecef8_ @ 0x801ecef8  (18 instructions)
 *
 *   801ecef8  9421fff0  stwu r1, -0x10(r1)
 *   801ecefc  7c0802a6  mflr r0
 *   801ecf00  90010014  stw r0, 0x14(r1)
 *   801ecf04  4be9d269  bl 0x8008a16c
 *   801ecf08  38600028  li r3, 0x28
 *   801ecf0c  4be9ccf5  bl 0x80089c00
 *   801ecf10  38600038  li r3, 0x38
 *   801ecf14  4be9cced  bl 0x80089c00
 *   801ecf18  3c608009  lis r3, -0x7ff7
 *   801ecf1c  38639eb4  addi r3, r3, -0x614c
 *   801ecf20  4be9f1bd  bl 0x8008c0dc
 *   801ecf24  3c608009  lis r3, -0x7ff7
 *   801ecf28  38639f28  addi r3, r3, -0x60d8
 *   801ecf2c  4be9f1d9  bl 0x8008c104
 *   801ecf30  80010014  lwz r0, 0x14(r1)
 *   801ecf34  7c0803a6  mtlr r0
 *   801ecf38  38210010  addi r1, r1, 0x10
 *   801ecf3c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl li bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2fc1011c4cd46e42d5baedd592ac63f360243764fb823e011743a97430cb7565
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
    zz_0089c00_(0x28);
    zz_0089c00_(0x38);
    zz_008c0dc_(&DAT_80089eb4);
    return zz_008c104_(&DAT_80089f28);
}
