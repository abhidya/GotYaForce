/* MATCHED  gnt4-acos-bl @ 0x8023cb38  (8 instructions)
 *
 *   8023cb38  9421fff0  stwu r1, -0x10(r1)
 *   8023cb3c  7c0802a6  mflr r0
 *   8023cb40  90010014  stw r0, 0x14(r1)
 *   8023cb44  4bffc8cd  bl 0x80239410
 *   8023cb48  80010014  lwz r0, 0x14(r1)
 *   8023cb4c  7c0803a6  mtlr r0
 *   8023cb50  38210010  addi r1, r1, 0x10
 *   8023cb54  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 650591f95aec175ecbf210421e6c3127f38bd2cd3c54df4df2a93cff2c3a212d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80239410(void);

void f(void)
{
    FUN_80239410();
}
