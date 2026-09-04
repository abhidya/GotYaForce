/* MATCHED  zz_0080170_ @ 0x80080170  (3 instructions)
 *
 *   80080170  38000000  li r0, 0
 *   80080174  900dac14  stw r0, -0x53ec(r13)
 *   80080178  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : e14e5ee7a385c97c6e402034de0c8090706f4b76702363731874c0e5a73b502d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361b4;

void f(void)
{
    DAT_804361b4 = 0;
}
