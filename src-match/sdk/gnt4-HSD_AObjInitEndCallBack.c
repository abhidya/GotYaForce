/* MATCHED  gnt4-HSD_AObjInitEndCallBack @ 0x80243b24  (4 instructions)
 *
 *   80243b24  38000000  li r0, 0
 *   80243b28  900db390  stw r0, -0x4c70(r13)
 *   80243b2c  900db38c  stw r0, -0x4c74(r13)
 *   80243b30  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 6fac78f8c9eec99e449362a92288b728c0d7de7f1d137cd8cadf183084344b4b
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043692c;
extern int DAT_80436930;

void f(void)
{
    DAT_80436930 = 0;
    DAT_8043692c = 0;
}
