/* MATCHED  zz_01f5ffc_ @ 0x801f5ffc  (10 instructions)
 *
 *   801f5ffc  9421fff0  stwu r1, -0x10(r1)
 *   801f6000  7c0802a6  mflr r0
 *   801f6004  90010014  stw r0, 0x14(r1)
 *   801f6008  4be94165  bl 0x8008a16c
 *   801f600c  38600038  li r3, 0x38
 *   801f6010  4be93bf1  bl 0x80089c00
 *   801f6014  80010014  lwz r0, 0x14(r1)
 *   801f6018  7c0803a6  mtlr r0
 *   801f601c  38210010  addi r1, r1, 0x10
 *   801f6020  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw bl li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : dc91cb1c66af06f1d77128a58e500888029382563ce4194a68f3adeeacc6e259
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int zz_0089c00_(int);
extern int zz_008a16c_(void);

int f(void)
{
    zz_008a16c_();
    return zz_0089c00_(0x38);
}
