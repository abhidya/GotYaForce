/* MATCHED  zz_0174d0c_ @ 0x80174d0c  (13 instructions)
 *
 *   80174d0c  9421fff0  stwu r1, -0x10(r1)
 *   80174d10  7c0802a6  mflr r0
 *   80174d14  38600010  li r3, 0x10
 *   80174d18  90010014  stw r0, 0x14(r1)
 *   80174d1c  4bf14b7d  bl 0x80089898
 *   80174d20  38600038  li r3, 0x38
 *   80174d24  4bf14b75  bl 0x80089898
 *   80174d28  4bf1482d  bl 0x80089554
 *   80174d2c  4bf1492d  bl 0x80089658
 *   80174d30  80010014  lwz r0, 0x14(r1)
 *   80174d34  7c0803a6  mtlr r0
 *   80174d38  38210010  addi r1, r1, 0x10
 *   80174d3c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl li bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 772fcfb55094161b1630de4920aa4f26fd5e2308053f7e5bd9c8df14de4a1644
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089554_(void);
extern int zz_0089658_(void);
extern int zz_0089898_(int);

int f(void)
{
    zz_0089898_(0x10);
    zz_0089898_(0x38);
    zz_0089554_();
    return zz_0089658_();
}
