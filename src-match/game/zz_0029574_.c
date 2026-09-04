/* MATCHED  zz_0029574_ @ 0x80029574  (27 instructions)
 *
 *   80029574  9421fff0  stwu r1, -0x10(r1)
 *   80029578  7c0802a6  mflr r0
 *   8002957c  90010014  stw r0, 0x14(r1)
 *   80029580  48060bed  bl 0x8008a16c
 *   80029584  4802a3a5  bl 0x80053928
 *   80029588  38600028  li r3, 0x28
 *   8002958c  48060745  bl 0x80089cd0
 *   80029590  38600020  li r3, 0x20
 *   80029594  4806073d  bl 0x80089cd0
 *   80029598  38600000  li r3, 0
 *   8002959c  48060735  bl 0x80089cd0
 *   800295a0  38600010  li r3, 0x10
 *   800295a4  4806072d  bl 0x80089cd0
 *   800295a8  38600008  li r3, 8
 *   800295ac  48060725  bl 0x80089cd0
 *   800295b0  38600018  li r3, 0x18
 *   800295b4  4806071d  bl 0x80089cd0
 *   800295b8  3860003a  li r3, 0x3a
 *   800295bc  48060645  bl 0x80089c00
 *   800295c0  38600038  li r3, 0x38
 *   800295c4  4806063d  bl 0x80089c00
 *   800295c8  38600039  li r3, 0x39
 *   800295cc  48060635  bl 0x80089c00
 *   800295d0  80010014  lwz r0, 0x14(r1)
 *   800295d4  7c0803a6  mtlr r0
 *   800295d8  38210010  addi r1, r1, 0x10
 *   800295dc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl li bl li bl li bl li bl li bl li bl li bl li bl li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c7ee753ec78cf6e7e17be9d01018ee90a18d9c86947df5e725c7da1ac01862f1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0053928_(void);
extern int zz_0089c00_(int);
extern int zz_0089cd0_(int);
extern int zz_008a16c_(void);

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
    zz_0089c00_(0x3a);
    zz_0089c00_(0x38);
    return zz_0089c00_(0x39);
}
