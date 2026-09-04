/* MATCHED  zz_008b9f8_ @ 0x8008b9f8  (2 instructions)
 *
 *   8008b9f8  38600200  li r3, 0x200
 *   8008b9fc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li blr
 *   exact_bytes      : true
 *   source sha256    : a59353f626f3d8d03d881fc72040dfd8b8b4cf36e662589d44ec7c3daf7de6d1
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(void)
{
    return 0x200;
}
