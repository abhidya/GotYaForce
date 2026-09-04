/* MATCHED  zz_0094f5c_ @ 0x80094f5c  (16 instructions)
 *
 *   80094f5c  9421fff0  stwu r1, -0x10(r1)
 *   80094f60  7c0802a6  mflr r0
 *   80094f64  90010014  stw r0, 0x14(r1)
 *   80094f68  4bf73bf1  bl 0x80008b58
 *   80094f6c  48102965  bl 0x801978d0
 *   80094f70  38600000  li r3, 0
 *   80094f74  48054b4d  bl 0x800e9ac0
 *   80094f78  38600001  li r3, 1
 *   80094f7c  48054b45  bl 0x800e9ac0
 *   80094f80  38600002  li r3, 2
 *   80094f84  48054b3d  bl 0x800e9ac0
 *   80094f88  4805b83d  bl 0x800f07c4
 *   80094f8c  80010014  lwz r0, 0x14(r1)
 *   80094f90  7c0803a6  mtlr r0
 *   80094f94  38210010  addi r1, r1, 0x10
 *   80094f98  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl li bl li bl li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : d4f01b9b45f15dd9a6de2d0d3d9f6fcb2e8e334e1c1bfba52597b28ff554b102
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0008b58_(void);
extern int zz_00e9ac0_(int);
extern int zz_00f07c4_(void);
extern int zz_01978d0_(void);

int f(void)
{
    zz_0008b58_();
    zz_01978d0_();
    zz_00e9ac0_(0);
    zz_00e9ac0_(1);
    zz_00e9ac0_(2);
    return zz_00f07c4_();
}
