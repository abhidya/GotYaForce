/* MATCHED  gnt4-HSD_CObjSetMtxDirty-bl @ 0x80247b0c  (4 instructions)
 *
 *   80247b0c  80030008  lwz r0, 8(r3)
 *   80247b10  6400c000  oris r0, r0, 0xc000
 *   80247b14  90030008  stw r0, 8(r3)
 *   80247b18  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz oris stw blr
 *   exact_bytes      : true
 *   source sha256    : 206331083ca7e39e09120d2d0265077544a4e808a3a3f29871197935b3817bef
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int                  field_8;
} S0;

void f(S0 *p0)
{
    p0->field_8 = p0->field_8 | 0xc0000000;
}
