/* MATCHED  zz_0264678_ @ 0x80264678  (2 instructions)
 *
 *   80264678  38630058  addi r3, r3, 0x58
 *   8026467c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : addi blr
 *   exact_bytes      : true
 *   source sha256    : 13989f4f17f271d29b985a670e27f48d93322e64dfc3a6063fb3f4ae6b6957ef
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(int p0)
{
    return p0 + 0x58;
}
