/* MATCHED  zz_0264630_ @ 0x80264630  (9 instructions)
 *
 *   80264630  9421fff0  stwu r1, -0x10(r1)
 *   80264634  7c0802a6  mflr r0
 *   80264638  90010014  stw r0, 0x14(r1)
 *   8026463c  80630004  lwz r3, 4(r3)
 *   80264640  48003ce5  bl 0x80268324
 *   80264644  80010014  lwz r0, 0x14(r1)
 *   80264648  7c0803a6  mtlr r0
 *   8026464c  38210010  addi r1, r1, 0x10
 *   80264650  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4b55c1af4639cb6e403368f22dc0f03a4b2f82f7f3a595a22669d250a2bb65bc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
} S0;

extern int zz_0268324_(int);

int f(S0 *p0)
{
    return zz_0268324_(p0->field_4);
}
