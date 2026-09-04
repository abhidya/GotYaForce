/* MATCHED  zz_008d790_ @ 0x8008d790  (2 instructions)
 *
 *   8008d790  806dad10  lwz r3, -0x52f0(r13)
 *   8008d794  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 1eff62643b01e608ea0e41f87f5b66460aead1aa4f0f8941faf1489c41c3f439
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804362b0;

int f(void)
{
    return DAT_804362b0;
}
