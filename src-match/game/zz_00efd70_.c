/* MATCHED  zz_00efd70_ @ 0x800efd70  (14 instructions)
 *
 *   800efd70  9421fff0  stwu r1, -0x10(r1)
 *   800efd74  7c0802a6  mflr r0
 *   800efd78  3c60803d  lis r3, -0x7fc3
 *   800efd7c  38800000  li r4, 0
 *   800efd80  90010014  stw r0, 0x14(r1)
 *   800efd84  38633ae8  addi r3, r3, 0x3ae8
 *   800efd88  38a00358  li r5, 0x358
 *   800efd8c  4bf15681  bl 0x8000540c
 *   800efd90  48000ca5  bl 0x800f0a34
 *   800efd94  48000ccd  bl 0x800f0a60
 *   800efd98  80010014  lwz r0, 0x14(r1)
 *   800efd9c  7c0803a6  mtlr r0
 *   800efda0  38210010  addi r1, r1, 0x10
 *   800efda4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1c4dcd361e6f0f0169c4d10861415d5c4497ffb898e89d88cad1ca7f8a241a64
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803d3ae8;

extern int FUN_8000540c(int, int, int);
extern int zz_00f0a34_(void);
extern int zz_00f0a60_(void);

int f(void)
{
    FUN_8000540c(&DAT_803d3ae8, 0, 0x358);
    zz_00f0a34_();
    return zz_00f0a60_();
}
