/* MATCHED  TRKTargetSetInputPendingPtr @ 0x8022f95c  (4 instructions)
 *
 *   8022f95c  3c80803f  lis r4, -0x7fc1
 *   8022f960  388475dc  addi r4, r4, 0x75dc
 *   8022f964  90640098  stw r3, 0x98(r4)
 *   8022f968  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi stw blr
 *   exact_bytes      : false
 *   source sha256    : 21144926446f7ce6d60f827a73455f3dc47b1732df590a7776ea14506c98e2d1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803f75dc {
    char pad_0[0x98];
    int                  field_98;
} G803f75dc;

extern G803f75dc DAT_803f75dc;

void f(int p0)
{
    DAT_803f75dc.field_98 = p0;
}
