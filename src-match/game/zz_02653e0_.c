/* MATCHED  zz_02653e0_ @ 0x802653e0  (13 instructions)
 *
 *   802653e0  9421fff0  stwu r1, -0x10(r1)
 *   802653e4  7c0802a6  mflr r0
 *   802653e8  90010014  stw r0, 0x14(r1)
 *   802653ec  48003a75  bl 0x80268e60
 *   802653f0  3c608040  lis r3, -0x7fc0
 *   802653f4  38800000  li r4, 0
 *   802653f8  3863b670  addi r3, r3, -0x4990
 *   802653fc  38a009c0  li r5, 0x9c0
 *   80265400  4bda000d  bl 0x8000540c
 *   80265404  80010014  lwz r0, 0x14(r1)
 *   80265408  7c0803a6  mtlr r0
 *   8026540c  38210010  addi r1, r1, 0x10
 *   80265410  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lis li addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e005ffb0c1b3242437b1f17e4bfa7757ed47f78fad1db184a02f189bc1f3f516
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fb670;

extern int FUN_8000540c(int, int, int);
extern int zz_0268e60_(void);

int f(void)
{
    zz_0268e60_();
    return FUN_8000540c(&DAT_803fb670, 0, 0x9c0);
}
