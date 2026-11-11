/* MATCHED  zz_0181e30_ @ 0x80181e30  (18 instructions)
 *
 *   80181e30  9421fff0  stwu r1, -0x10(r1)
 *   80181e34  7c0802a6  mflr r0
 *   80181e38  90010014  stw r0, 0x14(r1)
 *   80181e3c  4bf08331  bl 0x8008a16c
 *   80181e40  38600039  li r3, 0x39
 *   80181e44  4bf07dbd  bl 0x80089c00
 *   80181e48  38600038  li r3, 0x38
 *   80181e4c  4bf07db5  bl 0x80089c00
 *   80181e50  3c608009  lis r3, -0x7ff7
 *   80181e54  38639eb4  addi r3, r3, -0x614c
 *   80181e58  4bf0a285  bl 0x8008c0dc
 *   80181e5c  3c608009  lis r3, -0x7ff7
 *   80181e60  38639f28  addi r3, r3, -0x60d8
 *   80181e64  4bf0a2a1  bl 0x8008c104
 *   80181e68  80010014  lwz r0, 0x14(r1)
 *   80181e6c  7c0803a6  mtlr r0
 *   80181e70  38210010  addi r1, r1, 0x10
 *   80181e74  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl li bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 06b04282f06e24689597502492314e19699ffb7d17c1ee6a1d365f4a69762596
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
    zz_0089c00_(0x39);
    zz_0089c00_(0x38);
    zz_008c0dc_(&DAT_80089eb4);
    return zz_008c104_(&DAT_80089f28);
}
