/* MATCHED  zz_0218550_ @ 0x80218550  (3 instructions)
 *
 *   80218550  3c60803e  lis r3, -0x7fc2
 *   80218554  3863fba0  addi r3, r3, -0x460
 *   80218558  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi blr
 *   exact_bytes      : false
 *   source sha256    : c2ac0fa4803975aaf30b2755e3e44bb6e1076a47bc6dcac44f7c2a632df0d552
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803dfba0;

int f(void)
{
    return &DAT_803dfba0;
}
