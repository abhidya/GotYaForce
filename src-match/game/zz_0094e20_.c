/* MATCHED  zz_0094e20_ @ 0x80094e20  (9 instructions)
 *
 *   80094e20  9421fff0  stwu r1, -0x10(r1)
 *   80094e24  7c0802a6  mflr r0
 *   80094e28  90010014  stw r0, 0x14(r1)
 *   80094e2c  48000019  bl 0x80094e44
 *   80094e30  48000049  bl 0x80094e78
 *   80094e34  80010014  lwz r0, 0x14(r1)
 *   80094e38  7c0803a6  mtlr r0
 *   80094e3c  38210010  addi r1, r1, 0x10
 *   80094e40  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 9acb0ce66441b966bc72ca1b0fc1a4fdedfe6c6865ee8967fab5dffbebd5c4e5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0094e44_(void);
extern int zz_0094e78_(void);

int f(void)
{
    zz_0094e44_();
    return zz_0094e78_();
}
