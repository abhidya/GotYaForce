/* MATCHED  zz_0264710_ @ 0x80264710  (9 instructions)
 *
 *   80264710  9421fff0  stwu r1, -0x10(r1)
 *   80264714  7c0802a6  mflr r0
 *   80264718  90010014  stw r0, 0x14(r1)
 *   8026471c  80630004  lwz r3, 4(r3)
 *   80264720  48003cbd  bl 0x802683dc
 *   80264724  80010014  lwz r0, 0x14(r1)
 *   80264728  7c0803a6  mtlr r0
 *   8026472c  38210010  addi r1, r1, 0x10
 *   80264730  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b5942eeab12498aba78b0fb2c7484167a7f941cf8489d55a499a08d7ca02b646
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_02683dc_(int);

int f(S0 *p0)
{
    return zz_02683dc_(p0->field_4);
}
