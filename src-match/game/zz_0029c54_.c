/* MATCHED  zz_0029c54_ @ 0x80029c54  (20 instructions)
 *
 *   80029c54  9421fff0  stwu r1, -0x10(r1)
 *   80029c58  7c0802a6  mflr r0
 *   80029c5c  90010014  stw r0, 0x14(r1)
 *   80029c60  4bfdeef9  bl 0x80008b58
 *   80029c64  4bfdefdd  bl 0x80008c40
 *   80029c68  4bfdf08d  bl 0x80008cf4
 *   80029c6c  4816dc65  bl 0x801978d0
 *   80029c70  48016ca1  bl 0x80040910
 *   80029c74  480c6ded  bl 0x800f0a60
 *   80029c78  38600000  li r3, 0
 *   80029c7c  480bfe45  bl 0x800e9ac0
 *   80029c80  38600001  li r3, 1
 *   80029c84  480bfe3d  bl 0x800e9ac0
 *   80029c88  38600002  li r3, 2
 *   80029c8c  480bfe35  bl 0x800e9ac0
 *   80029c90  480c6b35  bl 0x800f07c4
 *   80029c94  80010014  lwz r0, 0x14(r1)
 *   80029c98  7c0803a6  mtlr r0
 *   80029c9c  38210010  addi r1, r1, 0x10
 *   80029ca0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl bl bl bl bl li bl li bl li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2ea41a32717e443f01c1aeb166995df5e3a61bf33cfc3481117d953801554667
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0008b58_(void);
extern int zz_0008c40_(void);
extern int zz_0008cf4_(void);
extern int zz_0040910_(void);
extern int zz_00e9ac0_(int);
extern int zz_00f07c4_(void);
extern int zz_00f0a60_(void);
extern int zz_01978d0_(void);

int f(void)
{
    zz_0008b58_();
    zz_0008c40_();
    zz_0008cf4_();
    zz_01978d0_();
    zz_0040910_();
    zz_00f0a60_();
    zz_00e9ac0_(0);
    zz_00e9ac0_(1);
    zz_00e9ac0_(2);
    return zz_00f07c4_();
}
