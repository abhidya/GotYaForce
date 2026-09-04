/* MATCHED  zz_01b2b28_ @ 0x801b2b28  (15 instructions)
 *
 *   801b2b28  9421fff0  stwu r1, -0x10(r1)
 *   801b2b2c  7c0802a6  mflr r0
 *   801b2b30  90010014  stw r0, 0x14(r1)
 *   801b2b34  a8830548  lha r4, 0x548(r3)
 *   801b2b38  3804ffff  addi r0, r4, -1
 *   801b2b3c  b0030548  sth r0, 0x548(r3)
 *   801b2b40  a8030548  lha r0, 0x548(r3)
 *   801b2b44  2c000000  cmpwi r0, 0
 *   801b2b48  4181000c  bgt 0x801b2b54
 *   801b2b4c  38800000  li r4, 0
 *   801b2b50  4beb79ed  bl 0x8006a53c
 *   801b2b54  80010014  lwz r0, 0x14(r1)
 *   801b2b58  7c0803a6  mtlr r0
 *   801b2b5c  38210010  addi r1, r1, 0x10
 *   801b2b60  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lha addi sth lha cmpwi bgt li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 24599a077c42f036cbd4ac0886b584532d96547f9c3b37228281d3484a405a69
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x548];
    short                field_548;
} S0;

extern int zz_006a53c_(int, int);

void f(S0 *p0)
{
    p0->field_548 = p0->field_548 + -1;
    if (p0->field_548 <= 0)
        zz_006a53c_(p0, 0);
}
