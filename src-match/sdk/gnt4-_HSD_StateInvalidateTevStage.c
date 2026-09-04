/* MATCHED  gnt4-_HSD_StateInvalidateTevStage @ 0x8024226c  (3 instructions)
 *
 *   8024226c  38000000  li r0, 0
 *   80242270  900db370  stw r0, -0x4c90(r13)
 *   80242274  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : e82a0260dbedbc2cb3a94aa5c0e76803b53d70de4b56604277751c1dfb56fd76
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436910;

void f(void)
{
    DAT_80436910 = 0;
}
