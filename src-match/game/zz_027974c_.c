/* MATCHED  zz_027974c_ @ 0x8027974c  (4 instructions)
 *
 *   8027974c  28030000  cmplwi r3, 0
 *   80279750  4d820020  beqlr
 *   80279754  98830003  stb r4, 3(r3)
 *   80279758  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr stb blr
 *   exact_bytes      : true
 *   source sha256    : cc0a56a124223245ea965e70712423e799e5e0d5cf979c19645bcd65c0be75eb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x3];
    char           field_3;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_3 = p1;
}
