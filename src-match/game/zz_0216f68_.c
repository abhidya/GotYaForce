/* MATCHED  zz_0216f68_ @ 0x80216f68  (4 instructions)
 *
 *   80216f68  800db110  lwz r0, -0x4ef0(r13)
 *   80216f6c  90030008  stw r0, 8(r3)
 *   80216f70  906db110  stw r3, -0x4ef0(r13)
 *   80216f74  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw stw blr
 *   exact_bytes      : false
 *   source sha256    : bbf066755208cc217b9a004849366f6c6169a077c4899572e536aa100bed90b0
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int                  field_8;
} S0;

extern int DAT_804366b0;

void f(S0 *p0)
{
    p0->field_8 = DAT_804366b0;
    DAT_804366b0 = p0;
}
