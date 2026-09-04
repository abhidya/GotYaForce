/* MATCHED  zz_007fd5c_ @ 0x8007fd5c  (4 instructions)
 *
 *   8007fd5c  38000000  li r0, 0
 *   8007fd60  900dac0c  stw r0, -0x53f4(r13)
 *   8007fd64  900dac08  stw r0, -0x53f8(r13)
 *   8007fd68  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 180177e23bac7bacb7bb1ef962fd3d4e64e603df18db0a8d99c63b63a12840cc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361a8;
extern int DAT_804361ac;

void f(void)
{
    DAT_804361ac = 0;
    DAT_804361a8 = 0;
}
