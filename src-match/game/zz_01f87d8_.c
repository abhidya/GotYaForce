/* MATCHED  zz_01f87d8_ @ 0x801f87d8  (13 instructions)
 *
 *   801f87d8  9421fff0  stwu r1, -0x10(r1)
 *   801f87dc  7c0802a6  mflr r0
 *   801f87e0  3c60803c  lis r3, -0x7fc4
 *   801f87e4  38800000  li r4, 0
 *   801f87e8  90010014  stw r0, 0x14(r1)
 *   801f87ec  386373b0  addi r3, r3, 0x73b0
 *   801f87f0  38a003e4  li r5, 0x3e4
 *   801f87f4  4be0cc19  bl 0x8000540c
 *   801f87f8  48000015  bl 0x801f880c
 *   801f87fc  80010014  lwz r0, 0x14(r1)
 *   801f8800  7c0803a6  mtlr r0
 *   801f8804  38210010  addi r1, r1, 0x10
 *   801f8808  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 40724b537b2eb171ddf3a5e25d78fdbd95ac10425cd0981901314d40bb82b9ea
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803c73b0;

extern int FUN_8000540c(int, int, int);
extern int zz_01f880c_(void);

int f(void)
{
    FUN_8000540c(&DAT_803c73b0, 0, 0x3e4);
    return zz_01f880c_();
}
