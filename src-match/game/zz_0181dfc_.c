/* MATCHED  zz_0181dfc_ @ 0x80181dfc  (13 instructions)
 *
 *   80181dfc  9421fff0  stwu r1, -0x10(r1)
 *   80181e00  7c0802a6  mflr r0
 *   80181e04  38600039  li r3, 0x39
 *   80181e08  90010014  stw r0, 0x14(r1)
 *   80181e0c  4bf07a8d  bl 0x80089898
 *   80181e10  38600038  li r3, 0x38
 *   80181e14  4bf07a85  bl 0x80089898
 *   80181e18  4bf0773d  bl 0x80089554
 *   80181e1c  4bf0783d  bl 0x80089658
 *   80181e20  80010014  lwz r0, 0x14(r1)
 *   80181e24  7c0803a6  mtlr r0
 *   80181e28  38210010  addi r1, r1, 0x10
 *   80181e2c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw bl li bl bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 133d9480e8ea44b471c4a497d900e962fa3f2813ab90fd3180afad1e09cc2149
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089554_(void);
extern int zz_0089658_(void);
extern int zz_0089898_(int);

int f(void)
{
    zz_0089898_(0x39);
    zz_0089898_(0x38);
    zz_0089554_();
    return zz_0089658_();
}
