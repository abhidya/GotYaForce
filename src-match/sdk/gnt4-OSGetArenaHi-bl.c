/* MATCHED  gnt4-OSGetArenaHi-bl @ 0x80200310  (2 instructions)
 *
 *   80200310  806dae78  lwz r3, -0x5188(r13)
 *   80200314  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : b6b3ce15c4dc629ec17f5f0c6e63b3db0546cf3521afb6af1b58946a7fcd9a71
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436418;

int f(void)
{
    return DAT_80436418;
}
