/* MATCHED  zz_0044ddc_ @ 0x80044ddc  (11 instructions)
 *
 *   80044ddc  9421fff0  stwu r1, -0x10(r1)
 *   80044de0  7c0802a6  mflr r0
 *   80044de4  3c60803c  lis r3, -0x7fc4
 *   80044de8  90010014  stw r0, 0x14(r1)
 *   80044dec  3863b32c  addi r3, r3, -0x4cd4
 *   80044df0  80630038  lwz r3, 0x38(r3)
 *   80044df4  48152ce5  bl 0x80197ad8
 *   80044df8  80010014  lwz r0, 0x14(r1)
 *   80044dfc  7c0803a6  mtlr r0
 *   80044e00  38210010  addi r1, r1, 0x10
 *   80044e04  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c063a3a7e09f006351acaadca9e9a8e7fc84e27e13405cf0f09803f9078459ee
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803bb32c {
    char pad_0[0x38];
    int                  field_38;
} G803bb32c;

extern G803bb32c DAT_803bb32c;

extern int zz_0197ad8_(int);

int f(void)
{
    return zz_0197ad8_(DAT_803bb32c.field_38);
}
