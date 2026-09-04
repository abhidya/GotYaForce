/* MATCHED  zz_0060e94_ @ 0x80060e94  (12 instructions)
 *
 *   80060e94  9421fff0  stwu r1, -0x10(r1)
 *   80060e98  7c0802a6  mflr r0
 *   80060e9c  90010014  stw r0, 0x14(r1)
 *   80060ea0  8803057e  lbz r0, 0x57e(r3)
 *   80060ea4  7c000775  extsb. r0, r0
 *   80060ea8  4082000c  bne 0x80060eb4
 *   80060eac  3880000d  li r4, 0xd
 *   80060eb0  4bfebe75  bl 0x8004cd24
 *   80060eb4  80010014  lwz r0, 0x14(r1)
 *   80060eb8  7c0803a6  mtlr r0
 *   80060ebc  38210010  addi r1, r1, 0x10
 *   80060ec0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lbz extsb. bne li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 12bfc4d8d3fb9ec6fe51229465404d21e707d1f7babfdf6ad91dea4ce24df033
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x57e];
    char                 field_57e;
} S0;

extern int zz_004cd24_(int, int);

void f(S0 *p0)
{
    if (p0->field_57e == 0)
        zz_004cd24_(p0, 0xd);
}
