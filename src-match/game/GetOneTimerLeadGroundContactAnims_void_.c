/* MATCHED  GetOneTimerLeadGroundContactAnims(void) @ 0x802ae100  (3 instructions)
 *
 *   802ae100  3c608043  lis r3, -0x7fbd
 *   802ae104  38631084  addi r3, r3, 0x1084
 *   802ae108  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi blr
 *   exact_bytes      : false
 *   source sha256    : a8879bf96505ffb7d4e42193704c8cd127ae386cad6c05c6b2944bb40c083c1d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_80431084;

int f(void)
{
    return &DAT_80431084;
}
