/* MATCHED  zz_0044630_ @ 0x80044630  (11 instructions)
 *
 *   80044630  9421fff0  stwu r1, -0x10(r1)
 *   80044634  7c0802a6  mflr r0
 *   80044638  3c60803c  lis r3, -0x7fc4
 *   8004463c  90010014  stw r0, 0x14(r1)
 *   80044640  3863b32c  addi r3, r3, -0x4cd4
 *   80044644  80630028  lwz r3, 0x28(r3)
 *   80044648  48153491  bl 0x80197ad8
 *   8004464c  80010014  lwz r0, 0x14(r1)
 *   80044650  7c0803a6  mtlr r0
 *   80044654  38210010  addi r1, r1, 0x10
 *   80044658  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 1fac21c81eb7dc2655a65dfab15370b4a7fb672dde4c9e2630ea92a4c45455df
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803bb32c {
    char pad_0[0x28];
    int                  field_28;
} G803bb32c;

extern G803bb32c DAT_803bb32c;

extern int zz_0197ad8_(int);

int f(void)
{
    return zz_0197ad8_(DAT_803bb32c.field_28);
}
