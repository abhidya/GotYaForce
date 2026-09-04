/* MATCHED  gnt4-HSD_DObjSetCurrent-bl @ 0x8023d768  (2 instructions)
 *
 *   8023d768  906db30c  stw r3, -0x4cf4(r13)
 *   8023d76c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : fd6caeeaabb6aabdec49e850d7bde4b44d413aad55c457d5826e334a20378784
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368ac;

void f(int p0)
{
    DAT_804368ac = p0;
}
