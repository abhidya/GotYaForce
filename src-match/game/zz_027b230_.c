/* MATCHED  zz_027b230_ @ 0x8027b230  (2 instructions)
 *
 *   8027b230  90830030  stw r4, 0x30(r3)
 *   8027b234  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 6c3f88edb50ce4c17b69fb39393d7968e368015092f6cba042f3f613aa7a0c44
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x30];
    int            field_30;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_30 = p1;
}
