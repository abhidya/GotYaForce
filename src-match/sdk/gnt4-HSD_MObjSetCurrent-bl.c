/* MATCHED  gnt4-HSD_MObjSetCurrent-bl @ 0x802422a4  (2 instructions)
 *
 *   802422a4  906db37c  stw r3, -0x4c84(r13)
 *   802422a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : a4c31f325ea2c6e8de2a40b85405934ede4ae8513f3e2db6f847e40cfbdb1f15
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043691c;

void f(int p0)
{
    DAT_8043691c = p0;
}
