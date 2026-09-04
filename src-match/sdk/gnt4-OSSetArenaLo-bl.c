/* MATCHED  gnt4-OSSetArenaLo-bl @ 0x80200328  (2 instructions)
 *
 *   80200328  906da6c8  stw r3, -0x5938(r13)
 *   8020032c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : e9c3a72b7960f9b8b39913c53601c449ea4aa31b9259269439a78d375dc7a832
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80435c68;

void f(int p0)
{
    DAT_80435c68 = p0;
}
