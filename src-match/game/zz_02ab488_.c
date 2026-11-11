/* MATCHED  zz_02ab488_ @ 0x802ab488  (12 instructions)
 *
 *   802ab488  9421fff0  stwu r1, -0x10(r1)
 *   802ab48c  7c0802a6  mflr r0
 *   802ab490  90010014  stw r0, 0x14(r1)
 *   802ab494  4bfd03a9  bl 0x8027b83c
 *   802ab498  3c60802b  lis r3, -0x7fd5
 *   802ab49c  38800000  li r4, 0
 *   802ab4a0  3863b460  addi r3, r3, -0x4ba0
 *   802ab4a4  4bfd0385  bl 0x8027b828
 *   802ab4a8  80010014  lwz r0, 0x14(r1)
 *   802ab4ac  7c0803a6  mtlr r0
 *   802ab4b0  38210010  addi r1, r1, 0x10
 *   802ab4b4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lis li addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4d25cf9e1b6a003e9240920e707b9431a9a06459e36da9704f62d351b41fab28
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_802ab460;

extern int zz_027b828_(int, int);
extern int zz_027b83c_(void);

int f(void)
{
    zz_027b83c_();
    return zz_027b828_(&DAT_802ab460, 0);
}
