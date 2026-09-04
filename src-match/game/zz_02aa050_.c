/* MATCHED  zz_02aa050_ @ 0x802aa050  (9 instructions)
 *
 *   802aa050  9421fff0  stwu r1, -0x10(r1)
 *   802aa054  7c0802a6  mflr r0
 *   802aa058  90010014  stw r0, 0x14(r1)
 *   802aa05c  80630040  lwz r3, 0x40(r3)
 *   802aa060  4bfee7f5  bl 0x80298854
 *   802aa064  80010014  lwz r0, 0x14(r1)
 *   802aa068  7c0803a6  mtlr r0
 *   802aa06c  38210010  addi r1, r1, 0x10
 *   802aa070  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 74197636b013a82589da0ec830cb4409b4f542b09e5b105f9697c5a61d03adcd
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x40];
    int                  field_40;
} S0;

extern int zz_0298854_(int);

int f(S0 *p0)
{
    return zz_0298854_(p0->field_40);
}
