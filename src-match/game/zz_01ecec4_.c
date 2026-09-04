/* MATCHED  zz_01ecec4_ @ 0x801ecec4  (13 instructions)
 *
 *   801ecec4  9421fff0  stwu r1, -0x10(r1)
 *   801ecec8  7c0802a6  mflr r0
 *   801ececc  38600028  li r3, 0x28
 *   801eced0  90010014  stw r0, 0x14(r1)
 *   801eced4  4be9c9c5  bl 0x80089898
 *   801eced8  38600038  li r3, 0x38
 *   801ecedc  4be9c9bd  bl 0x80089898
 *   801ecee0  4be9c675  bl 0x80089554
 *   801ecee4  4be9c775  bl 0x80089658
 *   801ecee8  80010014  lwz r0, 0x14(r1)
 *   801eceec  7c0803a6  mtlr r0
 *   801ecef0  38210010  addi r1, r1, 0x10
 *   801ecef4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl li bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 98b9f5289e8c299bb4d61447e8c5fd5e9d8f1f8f7ce65a4de4866fd3ceedc978
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089554_(void);
extern int zz_0089658_(void);
extern int zz_0089898_(int);

int f(void)
{
    zz_0089898_(0x28);
    zz_0089898_(0x38);
    zz_0089554_();
    return zz_0089658_();
}
