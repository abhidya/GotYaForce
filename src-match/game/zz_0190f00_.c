/* MATCHED  zz_0190f00_ @ 0x80190f00  (13 instructions)
 *
 *   80190f00  9421fff0  stwu r1, -0x10(r1)
 *   80190f04  7c0802a6  mflr r0
 *   80190f08  3c60803c  lis r3, -0x7fc4
 *   80190f0c  38800000  li r4, 0
 *   80190f10  90010014  stw r0, 0x14(r1)
 *   80190f14  386373b0  addi r3, r3, 0x73b0
 *   80190f18  38a003e4  li r5, 0x3e4
 *   80190f1c  4be744f1  bl 0x8000540c
 *   80190f20  48000015  bl 0x80190f34
 *   80190f24  80010014  lwz r0, 0x14(r1)
 *   80190f28  7c0803a6  mtlr r0
 *   80190f2c  38210010  addi r1, r1, 0x10
 *   80190f30  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 14c8f6e28dd71872d5a830bac12a4f0958ec472510109adf49edeb8621825b3f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803c73b0;

extern int FUN_8000540c(int, int, int);
extern int zz_0190f34_(void);

int f(void)
{
    FUN_8000540c(&DAT_803c73b0, 0, 0x3e4);
    return zz_0190f34_();
}
