/* MATCHED  zz_000a144_ @ 0x8000a144  (4 instructions)
 *
 *   8000a144  38000000  li r0, 0
 *   8000a148  900dab2c  stw r0, -0x54d4(r13)
 *   8000a14c  900dab28  stw r0, -0x54d8(r13)
 *   8000a150  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 2448eddeb31fc94f06b6685044915114fcff5e2ede1d85780ecd1eaeddfbf3b6
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804360c8;
extern int DAT_804360cc;

void f(void)
{
    DAT_804360cc = 0;
    DAT_804360c8 = 0;
}
