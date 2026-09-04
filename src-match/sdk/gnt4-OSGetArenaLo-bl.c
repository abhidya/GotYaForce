/* MATCHED  gnt4-OSGetArenaLo-bl @ 0x80200318  (2 instructions)
 *
 *   80200318  806da6c8  lwz r3, -0x5938(r13)
 *   8020031c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 587f95be55fc6de10c3f923d694898653718718cb7e3eb945ba2f116ad018ff2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80435c68;

int f(void)
{
    return DAT_80435c68;
}
