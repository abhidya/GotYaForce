/* MATCHED  zz_027b304_ @ 0x8027b304  (3 instructions)
 *
 *   8027b304  90830008  stw r4, 8(r3)
 *   8027b308  90a3000c  stw r5, 0xc(r3)
 *   8027b30c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : dce3ad88ca1d8baf1ccab3030110357aaa90a6a1038384094e56bb84fc700a40
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int            field_8;
    int            field_c;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_8 = p1;
    p0->field_c = p2;
}
