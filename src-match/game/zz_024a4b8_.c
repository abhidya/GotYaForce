/* MATCHED  zz_024a4b8_ @ 0x8024a4b8  (6 instructions)
 *
 *   8024a4b8  28030000  cmplwi r3, 0
 *   8024a4bc  4d820020  beqlr
 *   8024a4c0  a003000c  lhz r0, 0xc(r3)
 *   8024a4c4  7c002378  or r0, r0, r4
 *   8024a4c8  b003000c  sth r0, 0xc(r3)
 *   8024a4cc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (5 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 5
 *   shape            : cmplwi beqlr lhz or sth blr
 *   exact_bytes      : true
 *   source sha256    : 97bd9c45dcd9ddd7c6db90cd25fe6ae567646c680fcfda675dd2e050ebba9cb2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    unsigned short                field_c;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_c = p0->field_c | p1;
}
