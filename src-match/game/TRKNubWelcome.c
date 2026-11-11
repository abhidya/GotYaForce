/* MATCHED  TRKNubWelcome @ 0x8022ce28  (10 instructions)
 *
 *   8022ce28  9421fff0  stwu r1, -0x10(r1)
 *   8022ce2c  7c0802a6  mflr r0
 *   8022ce30  3c60802b  lis r3, -0x7fd5
 *   8022ce34  90010014  stw r0, 0x14(r1)
 *   8022ce38  386344c0  addi r3, r3, 0x44c0
 *   8022ce3c  4800498d  bl 0x802317c8
 *   8022ce40  80010014  lwz r0, 0x14(r1)
 *   8022ce44  7c0803a6  mtlr r0
 *   8022ce48  38210010  addi r1, r1, 0x10
 *   8022ce4c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9547cd8e391d3d603dc062aba0e3a2299877cb04601c05a65ced3defca0c6883
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_802b44c0;

extern int TRK_board_display(int);

int f(void)
{
    return TRK_board_display(&DAT_802b44c0);
}
