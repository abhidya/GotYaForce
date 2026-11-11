/* MATCHED  zz_0268c30_ @ 0x80268c30  (19 instructions)
 *
 *   80268c30  9421fff0  stwu r1, -0x10(r1)
 *   80268c34  7c0802a6  mflr r0
 *   80268c38  90010014  stw r0, 0x14(r1)
 *   80268c3c  93e1000c  stw r31, 0xc(r1)
 *   80268c40  7c7f1b79  or. r31, r3, r3
 *   80268c44  41820024  beq 0x80268c68
 *   80268c48  807f0008  lwz r3, 8(r31)
 *   80268c4c  48007d09  bl 0x80270954
 *   80268c50  7fe3fb78  mr r3, r31
 *   80268c54  38800000  li r4, 0
 *   80268c58  38a000c8  li r5, 0xc8
 *   80268c5c  4bd9c7b1  bl 0x8000540c
 *   80268c60  38000000  li r0, 0
 *   80268c64  b01f0000  sth r0, 0(r31)
 *   80268c68  80010014  lwz r0, 0x14(r1)
 *   80268c6c  83e1000c  lwz r31, 0xc(r1)
 *   80268c70  7c0803a6  mtlr r0
 *   80268c74  38210010  addi r1, r1, 0x10
 *   80268c78  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw stw or. beq lwz bl mr li li bl li sth lwz lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : b61f37dfd055375e069b6099fb83d17da6a4d3f5629bf2e5b1d6bca03d6677cd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    short                field_0;
    char pad_2[0x6];
    int                  field_8;
} S0;

extern int FUN_8000540c(int, int, int);
extern int zz_0270954_(int);

void f(S0 *p0)
{
    if (p0 != 0)
    {
        zz_0270954_(p0->field_8);
        FUN_8000540c(p0, 0, 0xc8);
        p0->field_0 = 0;
    }
}
