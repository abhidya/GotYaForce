/* MATCHED  zz_0098214_ @ 0x80098214  (3 instructions)
 *
 *   80098214  3c60803d  lis r3, -0x7fc3
 *   80098218  3863cd44  addi r3, r3, -0x32bc
 *   8009821c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi blr
 *   exact_bytes      : false
 *   source sha256    : b3bcbe3fbce25d57804285961bda334de7c83df11c459411b7fbf6b1a31711d9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_803ccd44;

int f(void)
{
    return &DAT_803ccd44;
}
