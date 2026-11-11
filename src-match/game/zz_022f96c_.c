/* MATCHED  zz_022f96c_ @ 0x8022f96c  (4 instructions)
 *
 *   8022f96c  3c60803f  lis r3, -0x7fc1
 *   8022f970  386375dc  addi r3, r3, 0x75dc
 *   8022f974  80630098  lwz r3, 0x98(r3)
 *   8022f978  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi lwz blr
 *   exact_bytes      : false
 *   source sha256    : 2246b2b717cd0836fd3ad17ab38f91af35dd70cb45d757ef73237070d13d5e62
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803f75dc {
    char pad_0[0x98];
    int                  field_98;
} G803f75dc;

extern G803f75dc DAT_803f75dc;

int f(void)
{
    return DAT_803f75dc.field_98;
}
