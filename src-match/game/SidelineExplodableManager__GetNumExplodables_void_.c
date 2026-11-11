/* MATCHED  SidelineExplodableManager::GetNumExplodables(void) @ 0x80008a70  (9 instructions)
 *
 *   80008a70  9421fff0  stwu r1, -0x10(r1)
 *   80008a74  7c0802a6  mflr r0
 *   80008a78  90010014  stw r0, 0x14(r1)
 *   80008a7c  806dac70  lwz r3, -0x5390(r13)
 *   80008a80  4823f5d9  bl 0x80248058
 *   80008a84  80010014  lwz r0, 0x14(r1)
 *   80008a88  7c0803a6  mtlr r0
 *   80008a8c  38210010  addi r1, r1, 0x10
 *   80008a90  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5813bd1fe17a982bee8b3d3a18ef9b3b68cfd03e909a63bc96b808c090e4d322
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436210;

extern int FUN_80248058(int);

int f(void)
{
    return FUN_80248058(DAT_80436210);
}
