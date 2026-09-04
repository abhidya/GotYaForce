/* MATCHED  zz_0094e44_ @ 0x80094e44  (13 instructions)
 *
 *   80094e44  9421fff0  stwu r1, -0x10(r1)
 *   80094e48  7c0802a6  mflr r0
 *   80094e4c  38600039  li r3, 0x39
 *   80094e50  90010014  stw r0, 0x14(r1)
 *   80094e54  4bff4a45  bl 0x80089898
 *   80094e58  38600038  li r3, 0x38
 *   80094e5c  4bff4a3d  bl 0x80089898
 *   80094e60  4bff46f5  bl 0x80089554
 *   80094e64  4bff47f5  bl 0x80089658
 *   80094e68  80010014  lwz r0, 0x14(r1)
 *   80094e6c  7c0803a6  mtlr r0
 *   80094e70  38210010  addi r1, r1, 0x10
 *   80094e74  4e800020  blr
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
