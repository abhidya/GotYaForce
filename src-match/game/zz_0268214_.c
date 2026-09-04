/* MATCHED  zz_0268214_ @ 0x80268214  (18 instructions)
 *
 *   80268214  9421fff0  stwu r1, -0x10(r1)
 *   80268218  7c0802a6  mflr r0
 *   8026821c  90010014  stw r0, 0x14(r1)
 *   80268220  93e1000c  stw r31, 0xc(r1)
 *   80268224  7c7f1b78  mr r31, r3
 *   80268228  80030004  lwz r0, 4(r3)
 *   8026822c  2c000003  cmpwi r0, 3
 *   80268230  40820018  bne 0x80268248
 *   80268234  807f0008  lwz r3, 8(r31)
 *   80268238  4800863d  bl 0x80270874
 *   8026823c  38000000  li r0, 0
 *   80268240  901f008c  stw r0, 0x8c(r31)
 *   80268244  901f0004  stw r0, 4(r31)
 *   80268248  80010014  lwz r0, 0x14(r1)
 *   8026824c  83e1000c  lwz r31, 0xc(r1)
 *   80268250  7c0803a6  mtlr r0
 *   80268254  38210010  addi r1, r1, 0x10
 *   80268258  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw mr lwz cmpwi bne lwz bl li stw stw lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 640818e91b15416e4abb1b59a8dfb4ae56b8852210e3048611f9b8963f969a62
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x4];
    int                  field_4;
    int                  field_8;
    char pad_c[0x80];
    int                  field_8c;
} S0;

extern int zz_0270874_(int);

void f(S0 *p0)
{
    if (p0->field_4 == 3)
    {
        zz_0270874_(p0->field_8);
        p0->field_8c = 0;
        p0->field_4 = 0;
    }
}
