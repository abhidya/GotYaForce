/* MATCHED  zz_0007d40_ @ 0x80007d40  (10 instructions)
 *
 *   80007d40  9421fff0  stwu r1, -0x10(r1)
 *   80007d44  7c0802a6  mflr r0
 *   80007d48  38800014  li r4, 0x14
 *   80007d4c  90010014  stw r0, 0x14(r1)
 *   80007d50  8063000c  lwz r3, 0xc(r3)
 *   80007d54  4824581d  bl 0x8024d570
 *   80007d58  80010014  lwz r0, 0x14(r1)
 *   80007d5c  7c0803a6  mtlr r0
 *   80007d60  38210010  addi r1, r1, 0x10
 *   80007d64  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : e5104e4110366e1f4b9abc19836fb5f693752a307dd7d37c8bba5f1678581edb
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_024d570_(int, int);

int f(S0 *p0)
{
    return zz_024d570_(p0->field_c, 0x14);
}
