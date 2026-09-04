/* MATCHED  gnt4-HSD_CObjGetViewingMtxPtrDirect-bl @ 0x8024f5c0  (2 instructions)
 *
 *   8024f5c0  38630054  addi r3, r3, 0x54
 *   8024f5c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : addi blr
 *   exact_bytes      : true
 *   source sha256    : d03f13cebee644ef8bd2a58f038cd608e57f1c5ab42e182548bc0fcce04aa032
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
int f(int p0)
{
    return p0 + 0x54;
}
