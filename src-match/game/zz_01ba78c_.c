/* MATCHED  zz_01ba78c_ @ 0x801ba78c  (16 instructions)
 *
 *   801ba78c  9421fff0  stwu r1, -0x10(r1)
 *   801ba790  7c0802a6  mflr r0
 *   801ba794  90010014  stw r0, 0x14(r1)
 *   801ba798  4bfdd139  bl 0x801978d0
 *   801ba79c  4be4e3bd  bl 0x80008b58
 *   801ba7a0  38600000  li r3, 0
 *   801ba7a4  4bf2f31d  bl 0x800e9ac0
 *   801ba7a8  38600001  li r3, 1
 *   801ba7ac  4bf2f315  bl 0x800e9ac0
 *   801ba7b0  38600002  li r3, 2
 *   801ba7b4  4bf2f30d  bl 0x800e9ac0
 *   801ba7b8  4bf3600d  bl 0x800f07c4
 *   801ba7bc  80010014  lwz r0, 0x14(r1)
 *   801ba7c0  7c0803a6  mtlr r0
 *   801ba7c4  38210010  addi r1, r1, 0x10
 *   801ba7c8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl li bl li bl li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0bc40b4ac7f99c571a332fd58119fad636334d9f6d6b7543dfa523f080d57425
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
    zz_01978d0_();
    zz_0008b58_();
    zz_00e9ac0_(0);
    zz_00e9ac0_(1);
    zz_00e9ac0_(2);
    return zz_00f07c4_();
}
