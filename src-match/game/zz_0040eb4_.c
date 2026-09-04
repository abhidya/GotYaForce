/* MATCHED  zz_0040eb4_ @ 0x80040eb4  (10 instructions)
 *
 *   80040eb4  9421fff0  stwu r1, -0x10(r1)
 *   80040eb8  7c0802a6  mflr r0
 *   80040ebc  90010014  stw r0, 0x14(r1)
 *   80040ec0  90830014  stw r4, 0x14(r3)
 *   80040ec4  80a40000  lwz r5, 0(r4)
 *   80040ec8  4bfc5dc1  bl 0x80006c88
 *   80040ecc  80010014  lwz r0, 0x14(r1)
 *   80040ed0  7c0803a6  mtlr r0
 *   80040ed4  38210010  addi r1, r1, 0x10
 *   80040ed8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b243d82e73934280f8e91c25b310975ee42fa9f72c638a40de1f54a2b0d63f79
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x14];
    int                  field_14;
} S0;

typedef struct S1 {
    int                  field_0;
} S1;

extern int zz_0006c88_(int, int, int);

int f(S0 *p0, S1 *p1)
{
    p0->field_14 = p1;
    return zz_0006c88_(p0, p1, p1->field_0);
}
