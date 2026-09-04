/* MATCHED  zz_0268294_ @ 0x80268294  (6 instructions)
 *
 *   80268294  80030004  lwz r0, 4(r3)
 *   80268298  2c000000  cmpwi r0, 0
 *   8026829c  4c820020  bnelr
 *   802682a0  38000001  li r0, 1
 *   802682a4  90030004  stw r0, 4(r3)
 *   802682a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz cmpwi bnelr li stw blr
 *   exact_bytes      : true
 *   source sha256    : 85aae3e6ffad53e96dcf7c9376947b574f55da99f18d5ae4bc3f3061bbbeb681
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

void f(S0 *p0)
{
    if (p0->field_4 != 0)
        return;
    p0->field_4 = 1;
}
