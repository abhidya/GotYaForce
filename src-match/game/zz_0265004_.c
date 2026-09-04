/* MATCHED  zz_0265004_ @ 0x80265004  (9 instructions)
 *
 *   80265004  9421fff0  stwu r1, -0x10(r1)
 *   80265008  7c0802a6  mflr r0
 *   8026500c  90010014  stw r0, 0x14(r1)
 *   80265010  80630004  lwz r3, 4(r3)
 *   80265014  4800ce39  bl 0x80271e4c
 *   80265018  80010014  lwz r0, 0x14(r1)
 *   8026501c  7c0803a6  mtlr r0
 *   80265020  38210010  addi r1, r1, 0x10
 *   80265024  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2c5aedc7a97db7202932f0045ca00a1befc21ada3ff542eadbe792980aa2ff57
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_0271e4c_(int);

int f(S0 *p0)
{
    return zz_0271e4c_(p0->field_4);
}
