/* MATCHED  zz_01ecfe4_ @ 0x801ecfe4  (16 instructions)
 *
 *   801ecfe4  9421fff0  stwu r1, -0x10(r1)
 *   801ecfe8  7c0802a6  mflr r0
 *   801ecfec  90010014  stw r0, 0x14(r1)
 *   801ecff0  4be1bb69  bl 0x80008b58
 *   801ecff4  4bfaa8dd  bl 0x801978d0
 *   801ecff8  38600000  li r3, 0
 *   801ecffc  4befcac5  bl 0x800e9ac0
 *   801ed000  38600001  li r3, 1
 *   801ed004  4befcabd  bl 0x800e9ac0
 *   801ed008  38600002  li r3, 2
 *   801ed00c  4befcab5  bl 0x800e9ac0
 *   801ed010  4bf037b5  bl 0x800f07c4
 *   801ed014  80010014  lwz r0, 0x14(r1)
 *   801ed018  7c0803a6  mtlr r0
 *   801ed01c  38210010  addi r1, r1, 0x10
 *   801ed020  4e800020  blr
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
