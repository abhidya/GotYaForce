/* MATCHED  zz_0040910_ @ 0x80040910  (12 instructions)
 *
 *   80040910  9421fff0  stwu r1, -0x10(r1)
 *   80040914  7c0802a6  mflr r0
 *   80040918  3c60803c  lis r3, -0x7fc4
 *   8004091c  38800000  li r4, 0
 *   80040920  90010014  stw r0, 0x14(r1)
 *   80040924  3863b168  addi r3, r3, -0x4e98
 *   80040928  38a001c4  li r5, 0x1c4
 *   8004092c  4bfc4ae1  bl 0x8000540c
 *   80040930  80010014  lwz r0, 0x14(r1)
 *   80040934  7c0803a6  mtlr r0
 *   80040938  38210010  addi r1, r1, 0x10
 *   8004093c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0d040b1ceef8170747dfffc1b567888a577d302554a66af3c4d614eb6dbdd060
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803bb168;

extern int FUN_8000540c(int, int, int);

int f(void)
{
    return FUN_8000540c(&DAT_803bb168, 0, 0x1c4);
}
