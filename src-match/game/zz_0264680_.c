/* MATCHED  zz_0264680_ @ 0x80264680  (9 instructions)
 *
 *   80264680  9421fff0  stwu r1, -0x10(r1)
 *   80264684  7c0802a6  mflr r0
 *   80264688  90010014  stw r0, 0x14(r1)
 *   8026468c  80630004  lwz r3, 4(r3)
 *   80264690  48003d2d  bl 0x802683bc
 *   80264694  80010014  lwz r0, 0x14(r1)
 *   80264698  7c0803a6  mtlr r0
 *   8026469c  38210010  addi r1, r1, 0x10
 *   802646a0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 038c653359a98db19e5454dede8da8b5f4e330050593786cc764564397c6669a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683bc_(int);

int f(S0 *p0)
{
    return zz_02683bc_(p0->field_4);
}
