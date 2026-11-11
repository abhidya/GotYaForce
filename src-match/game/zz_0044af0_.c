/* MATCHED  zz_0044af0_ @ 0x80044af0  (11 instructions)
 *
 *   80044af0  9421fff0  stwu r1, -0x10(r1)
 *   80044af4  7c0802a6  mflr r0
 *   80044af8  3c60803c  lis r3, -0x7fc4
 *   80044afc  90010014  stw r0, 0x14(r1)
 *   80044b00  3863b32c  addi r3, r3, -0x4cd4
 *   80044b04  80630050  lwz r3, 0x50(r3)
 *   80044b08  48152fd1  bl 0x80197ad8
 *   80044b0c  80010014  lwz r0, 0x14(r1)
 *   80044b10  7c0803a6  mtlr r0
 *   80044b14  38210010  addi r1, r1, 0x10
 *   80044b18  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis stw addi lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 19ef3e2c42e4fc25941a6a24c2e3471aaac176bff35ac0f5a372be7f3dfdfd6a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G803bb32c {
    char pad_0[0x50];
    int                  field_50;
} G803bb32c;

extern G803bb32c DAT_803bb32c;

extern int zz_0197ad8_(int);

int f(void)
{
    return zz_0197ad8_(DAT_803bb32c.field_50);
}
