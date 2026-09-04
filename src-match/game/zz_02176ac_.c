/* MATCHED  zz_02176ac_ @ 0x802176ac  (2 instructions)
 *
 *   802176ac  806db158  lwz r3, -0x4ea8(r13)
 *   802176b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 1541bdcff29cbe2e56966bf99c2d2bc270d86e1a22b65d0367f5ca8480099623
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804366f8;

int f(void)
{
    return DAT_804366f8;
}
