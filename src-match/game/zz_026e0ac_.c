/* MATCHED  zz_026e0ac_ @ 0x8026e0ac  (13 instructions)
 *
 *   8026e0ac  9421fff0  stwu r1, -0x10(r1)
 *   8026e0b0  7c0802a6  mflr r0
 *   8026e0b4  3c608040  lis r3, -0x7fc0
 *   8026e0b8  38800000  li r4, 0
 *   8026e0bc  90010014  stw r0, 0x14(r1)
 *   8026e0c0  3863f2f8  addi r3, r3, -0xd08
 *   8026e0c4  38a00e60  li r5, 0xe60
 *   8026e0c8  4bd97345  bl 0x8000540c
 *   8026e0cc  80010014  lwz r0, 0x14(r1)
 *   8026e0d0  38600001  li r3, 1
 *   8026e0d4  7c0803a6  mtlr r0
 *   8026e0d8  38210010  addi r1, r1, 0x10
 *   8026e0dc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi li bl lwz li mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d8181bcd1867ae0444eb628ce3b2309a62483be8fc94051188e235bc8a7ee9aa
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803ff2f8;

extern int FUN_8000540c(int, int, int);

int f(void)
{
    FUN_8000540c(&DAT_803ff2f8, 0, 0xe60);
    return 1;
}
