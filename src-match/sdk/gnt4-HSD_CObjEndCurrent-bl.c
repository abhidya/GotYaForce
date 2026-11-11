/* MATCHED  gnt4-HSD_CObjEndCurrent-bl @ 0x80247088  (9 instructions)
 *
 *   80247088  9421fff0  stwu r1, -0x10(r1)
 *   8024708c  7c0802a6  mflr r0
 *   80247090  90010014  stw r0, 0x14(r1)
 *   80247094  4800c731  bl 0x802537c4
 *   80247098  4800c77d  bl 0x80253814
 *   8024709c  80010014  lwz r0, 0x14(r1)
 *   802470a0  7c0803a6  mtlr r0
 *   802470a4  38210010  addi r1, r1, 0x10
 *   802470a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e93aa9f86fd5adee15bb8f96801083a491714c1d227b8aef73d23ca883513121
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int FUN_802537c4(void);
extern int FUN_80253814(void);

int f(void)
{
    FUN_802537c4();
    return FUN_80253814();
}
