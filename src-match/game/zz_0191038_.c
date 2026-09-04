/* MATCHED  zz_0191038_ @ 0x80191038  (13 instructions)
 *
 *   80191038  9421fff0  stwu r1, -0x10(r1)
 *   8019103c  7c0802a6  mflr r0
 *   80191040  38600010  li r3, 0x10
 *   80191044  90010014  stw r0, 0x14(r1)
 *   80191048  4bef8851  bl 0x80089898
 *   8019104c  38600038  li r3, 0x38
 *   80191050  4bef8849  bl 0x80089898
 *   80191054  4bef8501  bl 0x80089554
 *   80191058  4bef8601  bl 0x80089658
 *   8019105c  80010014  lwz r0, 0x14(r1)
 *   80191060  7c0803a6  mtlr r0
 *   80191064  38210010  addi r1, r1, 0x10
 *   80191068  4e800020  blr
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
