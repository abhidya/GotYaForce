/* MATCHED  gnt4-asin-bl @ 0x8023cb58  (8 instructions)
 *
 *   8023cb58  9421fff0  stwu r1, -0x10(r1)
 *   8023cb5c  7c0802a6  mflr r0
 *   8023cb60  90010014  stw r0, 0x14(r1)
 *   8023cb64  4bffcbbd  bl 0x80239720
 *   8023cb68  80010014  lwz r0, 0x14(r1)
 *   8023cb6c  7c0803a6  mtlr r0
 *   8023cb70  38210010  addi r1, r1, 0x10
 *   8023cb74  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/wrapper (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : cac5c00c8188f66ee85941b3115bb3292b68d5f4f893669690660539bfaec1db
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern void FUN_80239720(void);

void f(void)
{
    FUN_80239720();
}
