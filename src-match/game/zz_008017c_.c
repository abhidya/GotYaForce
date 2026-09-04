/* MATCHED  zz_008017c_ @ 0x8008017c  (2 instructions)
 *
 *   8008017c  806dac14  lwz r3, -0x53ec(r13)
 *   80080180  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : f5caafc4e2065535e35c6fe9a3fcf9d09e8edbde8b331bf64fad4db4bc1e4eed
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361b4;

int f(void)
{
    return DAT_804361b4;
}
