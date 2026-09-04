/* MATCHED  __set_debug_bba @ 0x80003140  (3 instructions)
 *
 *   80003140  38000001  li r0, 1
 *   80003144  980daef8  stb r0, -0x5108(r13)
 *   80003148  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : false
 *   source sha256    : 5d60a441d0d640f79a27f50fbb063af39b263abec979b27668c0b2f75ceca463
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern char DAT_80436498;

void f(void)
{
    DAT_80436498 = 1;
}
