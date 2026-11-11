/* MATCHED  zz_0029770_ @ 0x80029770  (22 instructions)
 *
 *   80029770  9421fff0  stwu r1, -0x10(r1)
 *   80029774  7c0802a6  mflr r0
 *   80029778  90010014  stw r0, 0x14(r1)
 *   8002977c  480609f1  bl 0x8008a16c
 *   80029780  38600028  li r3, 0x28
 *   80029784  4806054d  bl 0x80089cd0
 *   80029788  38600039  li r3, 0x39
 *   8002978c  48060475  bl 0x80089c00
 *   80029790  4805e085  bl 0x80087814
 *   80029794  3c608009  lis r3, -0x7ff7
 *   80029798  38639eb4  addi r3, r3, -0x614c
 *   8002979c  48062941  bl 0x8008c0dc
 *   800297a0  3c608009  lis r3, -0x7ff7
 *   800297a4  38639f28  addi r3, r3, -0x60d8
 *   800297a8  4806295d  bl 0x8008c104
 *   800297ac  3c608009  lis r3, -0x7ff7
 *   800297b0  38639f9c  addi r3, r3, -0x6064
 *   800297b4  48062979  bl 0x8008c12c
 *   800297b8  80010014  lwz r0, 0x14(r1)
 *   800297bc  7c0803a6  mtlr r0
 *   800297c0  38210010  addi r1, r1, 0x10
 *   800297c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl li bl bl lis addi bl lis addi bl lis addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 7844cf8f67d76773991f633a21b609ad5ab27e2a16080571899c20e55db24e5c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80089eb4;
extern struct { int v; char pad_[8]; } DAT_80089f28;
extern struct { int v; char pad_[8]; } DAT_80089f9c;

extern int zz_0087814_(void);
extern int zz_0089c00_(int);
extern int zz_0089cd0_(int);
extern int zz_008a16c_(void);
extern int zz_008c0dc_(int);
extern int zz_008c104_(int);
extern int zz_008c12c_(int);

int f(void)
{
    zz_008a16c_();
    zz_0089cd0_(0x28);
    zz_0089c00_(0x39);
    zz_0087814_();
    zz_008c0dc_(&DAT_80089eb4);
    zz_008c104_(&DAT_80089f28);
    return zz_008c12c_(&DAT_80089f9c);
}
