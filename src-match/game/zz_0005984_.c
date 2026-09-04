/* MATCHED  zz_0005984_ @ 0x80005984  (2 instructions)
 *
 *   80005984  906dab20  stw r3, -0x54e0(r13)
 *   80005988  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : 7203c0c15c74c298e4d4b4224d7264a67dcbf59102427e603af782294141c12c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804360c0;

void f(int p0)
{
    DAT_804360c0 = p0;
}
