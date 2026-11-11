/* MATCHED  __sinit_AILoader_cpp @ 0x80236820  (4 instructions)
 *
 *   80236820  3c608023  lis r3, -0x7fdd
 *   80236824  380337d8  addi r0, r3, 0x37d8
 *   80236828  900db2c8  stw r0, -0x4d38(r13)
 *   8023682c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lis addi stw blr
 *   exact_bytes      : false
 *   source sha256    : 50db7fa3f5d86ac36b992d833d19ecb910c5552c59c936dae4789aadf60be6ca
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_802337d8;
extern int DAT_80436868;

void f(void)
{
    DAT_80436868 = &DAT_802337d8;
}
