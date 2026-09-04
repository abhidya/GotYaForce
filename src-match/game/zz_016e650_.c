/* MATCHED  zz_016e650_ @ 0x8016e650  (17 instructions)
 *
 *   8016e650  9421fff0  stwu r1, -0x10(r1)
 *   8016e654  7c0802a6  mflr r0
 *   8016e658  90010014  stw r0, 0x14(r1)
 *   8016e65c  48029275  bl 0x801978d0
 *   8016e660  4be9a4f9  bl 0x80008b58
 *   8016e664  4be9a2c1  bl 0x80008924
 *   8016e668  38600000  li r3, 0
 *   8016e66c  4bf7b455  bl 0x800e9ac0
 *   8016e670  38600001  li r3, 1
 *   8016e674  4bf7b44d  bl 0x800e9ac0
 *   8016e678  38600002  li r3, 2
 *   8016e67c  4bf7b445  bl 0x800e9ac0
 *   8016e680  4bf82145  bl 0x800f07c4
 *   8016e684  80010014  lwz r0, 0x14(r1)
 *   8016e688  7c0803a6  mtlr r0
 *   8016e68c  38210010  addi r1, r1, 0x10
 *   8016e690  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl bl li bl li bl li bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 19afc2e790e096538ab48cef1279aea8a621b5ef2801a776f7a13e31a346550d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0008924_(void);
extern int zz_0008b58_(void);
extern int zz_00e9ac0_(int);
extern int zz_00f07c4_(void);
extern int zz_01978d0_(void);

int f(void)
{
    zz_01978d0_();
    zz_0008b58_();
    zz_0008924_();
    zz_00e9ac0_(0);
    zz_00e9ac0_(1);
    zz_00e9ac0_(2);
    return zz_00f07c4_();
}
