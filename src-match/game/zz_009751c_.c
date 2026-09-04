/* MATCHED  zz_009751c_ @ 0x8009751c  (4 instructions)
 *
 *   8009751c  38000000  li r0, 0
 *   80097520  900dad88  stw r0, -0x5278(r13)
 *   80097524  900dad7c  stw r0, -0x5284(r13)
 *   80097528  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 832f0722e95792bb07e6fa9d4bef7f8dea3dc77734216a7b000e8e99fb6f4efb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043631c;
extern int DAT_80436328;

void f(void)
{
    DAT_80436328 = 0;
    DAT_8043631c = 0;
}
