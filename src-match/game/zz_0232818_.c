/* MATCHED  zz_0232818_ @ 0x80232818  (9 instructions)
 *
 *   80232818  9421fff0  stwu r1, -0x10(r1)
 *   8023281c  7c0802a6  mflr r0
 *   80232820  90010014  stw r0, 0x14(r1)
 *   80232824  80630000  lwz r3, 0(r3)
 *   80232828  4bfd0fb5  bl 0x802037dc
 *   8023282c  80010014  lwz r0, 0x14(r1)
 *   80232830  7c0803a6  mtlr r0
 *   80232834  38210010  addi r1, r1, 0x10
 *   80232838  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 2abb2dc7a9e629b36e2ab5bc71d778197a57090f0113d02670f24d94ded1b14c
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    int                  field_0;
} S0;

extern int FUN_802037dc(int);

int f(S0 *p0)
{
    return FUN_802037dc(p0->field_0);
}
