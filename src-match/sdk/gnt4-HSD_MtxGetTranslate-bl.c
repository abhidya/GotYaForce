/* MATCHED  gnt4-HSD_MtxGetTranslate-bl @ 0x802561e0  (7 instructions)
 *
 *   802561e0  c003000c  lfs f0, 0xc(r3)
 *   802561e4  d0040000  stfs f0, 0(r4)
 *   802561e8  c003001c  lfs f0, 0x1c(r3)
 *   802561ec  d0040004  stfs f0, 4(r4)
 *   802561f0  c003002c  lfs f0, 0x2c(r3)
 *   802561f4  d0040008  stfs f0, 8(r4)
 *   802561f8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lfs stfs lfs stfs lfs stfs blr
 *   exact_bytes      : true
 *   source sha256    : ceef845cac02d3fff261e9c87394de9362d5267caf16181fda9f5abde4233d10
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    float                field_c;
    char pad_10[0xc];
    float                field_1c;
    char pad_20[0xc];
    float                field_2c;
} S0;

typedef struct S1 {
    float                field_0;
    float                field_4;
    float                field_8;
} S1;

void f(S0 *p0, S1 *p1)
{
    p1->field_0 = p0->field_c;
    p1->field_4 = p0->field_1c;
    p1->field_8 = p0->field_2c;
}
