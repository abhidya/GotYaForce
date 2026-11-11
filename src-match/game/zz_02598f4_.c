/* MATCHED  zz_02598f4_ @ 0x802598f4  (17 instructions)
 *
 *   802598f4  9421fff0  stwu r1, -0x10(r1)
 *   802598f8  7c0802a6  mflr r0
 *   802598fc  90010014  stw r0, 0x14(r1)
 *   80259900  93e1000c  stw r31, 0xc(r1)
 *   80259904  7c7f1b79  or. r31, r3, r3
 *   80259908  4182001c  beq 0x80259924
 *   8025990c  807f0018  lwz r3, 0x18(r31)
 *   80259910  4bfea5a1  bl 0x80243eb0
 *   80259914  38000000  li r0, 0
 *   80259918  901f0018  stw r0, 0x18(r31)
 *   8025991c  807f001c  lwz r3, 0x1c(r31)
 *   80259920  4bffde45  bl 0x80257764
 *   80259924  80010014  lwz r0, 0x14(r1)
 *   80259928  83e1000c  lwz r31, 0xc(r1)
 *   8025992c  7c0803a6  mtlr r0
 *   80259930  38210010  addi r1, r1, 0x10
 *   80259934  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw or. beq lwz bl li stw lwz bl lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 11d7c9e8185d2702372ac7629f9cd6772e042f543b571b370773d558d3ffe4a2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x18];
    int                  field_18;
    int                  field_1c;
} S0;

extern int FUN_80243eb0(int);
extern int zz_0257764_(int);

void f(S0 *p0)
{
    if (p0 != 0)
    {
        FUN_80243eb0(p0->field_18);
        p0->field_18 = 0;
        zz_0257764_(p0->field_1c);
    }
}
