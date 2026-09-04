/* MATCHED  gnt4-HSD_CObjSetFlags-bl @ 0x80248164  (6 instructions)
 *
 *   80248164  28030000  cmplwi r3, 0
 *   80248168  4d820020  beqlr
 *   8024816c  80030008  lwz r0, 8(r3)
 *   80248170  7c002378  or r0, r0, r4
 *   80248174  90030008  stw r0, 8(r3)
 *   80248178  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : cmplwi beqlr lwz or stw blr
 *   exact_bytes      : true
 *   source sha256    : 3088a9a7f6678b0f4bc1fb6525e877d9d7277a772c756094ca6fcc014f2ea8b4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int                  field_8;
} S0;

void f(S0 *p0, int p1)
{
    if (p0 == 0)
        return;
    p0->field_8 = p0->field_8 | p1;
}
