/* MATCHED  zz_027b310_ @ 0x8027b310  (2 instructions)
 *
 *   8027b310  90830004  stw r4, 4(r3)
 *   8027b314  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : true
 *   source sha256    : 321b81f63b0b032e1264835f48d1062c415632818eaec10db4a0677c6aca542f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int            field_4;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_4 = p1;
}
