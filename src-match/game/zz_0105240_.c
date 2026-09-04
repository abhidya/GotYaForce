/* MATCHED  zz_0105240_ @ 0x80105240  (19 instructions)
 *
 *   80105240  9421fff0  stwu r1, -0x10(r1)
 *   80105244  7c0802a6  mflr r0
 *   80105248  90010014  stw r0, 0x14(r1)
 *   8010524c  93e1000c  stw r31, 0xc(r1)
 *   80105250  7c7f1b78  mr r31, r3
 *   80105254  4bf49f71  bl 0x8004f1c4
 *   80105258  7fe3fb78  mr r3, r31
 *   8010525c  48001239  bl 0x80106494
 *   80105260  7fe3fb78  mr r3, r31
 *   80105264  38800030  li r4, 0x30
 *   80105268  4bfc2285  bl 0x800c74ec
 *   8010526c  7fe3fb78  mr r3, r31
 *   80105270  38800031  li r4, 0x31
 *   80105274  4bfc2279  bl 0x800c74ec
 *   80105278  80010014  lwz r0, 0x14(r1)
 *   8010527c  83e1000c  lwz r31, 0xc(r1)
 *   80105280  7c0803a6  mtlr r0
 *   80105284  38210010  addi r1, r1, 0x10
 *   80105288  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr bl mr bl mr li bl mr li bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5550da81d4324ed58adea0e5a011718e3d7425c799846da32d0e83642826d2bf
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_004f1c4_(void);
extern int zz_00c74ec_(int, int);
extern int zz_0106494_(int);

int f(int p0)
{
    zz_004f1c4_();
    zz_0106494_(p0);
    zz_00c74ec_(p0, 0x30);
    return zz_00c74ec_(p0, 0x31);
}
