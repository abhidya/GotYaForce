/* MATCHED  zz_01b3688_ @ 0x801b3688  (9 instructions)
 *
 *   801b3688  9421fff0  stwu r1, -0x10(r1)
 *   801b368c  7c0802a6  mflr r0
 *   801b3690  38800043  li r4, 0x43
 *   801b3694  90010014  stw r0, 0x14(r1)
 *   801b3698  4bf13e55  bl 0x800c74ec
 *   801b369c  80010014  lwz r0, 0x14(r1)
 *   801b36a0  7c0803a6  mtlr r0
 *   801b36a4  38210010  addi r1, r1, 0x10
 *   801b36a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e1fcb616e627ea59deca0cfac2dfeec7f1e6b643977f648a25d0b7fe8e5c8a6c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void zz_00c74ec_(int, int);

void f(int p0)
{
    zz_00c74ec_(p0, 0x43);
}
