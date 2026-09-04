/* MATCHED  zz_023ccd8_ @ 0x8023ccd8  (2 instructions)
 *
 *   8023ccd8  38600001  li r3, 1
 *   8023ccdc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li blr
 *   exact_bytes      : true
 *   source sha256    : a29de7018f89a39d4c404a12a12a41c7b3b7fa8586c0aae516cee3a5c9b93c8f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(void)
{
    return 1;
}
