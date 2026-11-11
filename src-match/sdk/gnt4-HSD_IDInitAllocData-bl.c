/* MATCHED  gnt4-HSD_IDInitAllocData-bl @ 0x80259644  (12 instructions)
 *
 *   80259644  9421fff0  stwu r1, -0x10(r1)
 *   80259648  7c0802a6  mflr r0
 *   8025964c  3c608040  lis r3, -0x7fc0
 *   80259650  3880000c  li r4, 0xc
 *   80259654  90010014  stw r0, 0x14(r1)
 *   80259658  3863a530  addi r3, r3, -0x5ad0
 *   8025965c  38a00004  li r5, 4
 *   80259660  4bffde09  bl 0x80257468
 *   80259664  80010014  lwz r0, 0x14(r1)
 *   80259668  7c0803a6  mtlr r0
 *   8025966c  38210010  addi r1, r1, 0x10
 *   80259670  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 40ce5523b8a3ea35e2d86d51348c97aa07ff9aa3d39b0dc451bfd4cf99dd1f24
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803fa530;

extern int FUN_80257468(int, int, int);

int f(void)
{
    return FUN_80257468(&DAT_803fa530, 0xc, 4);
}
