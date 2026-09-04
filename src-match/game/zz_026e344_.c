/* MATCHED  zz_026e344_ @ 0x8026e344  (2 instructions)
 *
 *   8026e344  90830088  stw r4, 0x88(r3)
 *   8026e348  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 7df7a43dcdca1155e2426bb19e4ba9ca4421269961271fa665d6ff8045badc79
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x88];
    int            field_88;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_88 = p1;
}
