/* MATCHED  zz_02aac00_ @ 0x802aac00  (9 instructions)
 *
 *   802aac00  9421fff0  stwu r1, -0x10(r1)
 *   802aac04  7c0802a6  mflr r0
 *   802aac08  90010014  stw r0, 0x14(r1)
 *   802aac0c  806300a8  lwz r3, 0xa8(r3)
 *   802aac10  4bfd0f45  bl 0x8027bb54
 *   802aac14  80010014  lwz r0, 0x14(r1)
 *   802aac18  7c0803a6  mtlr r0
 *   802aac1c  38210010  addi r1, r1, 0x10
 *   802aac20  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 5b4b350a0b29df22087274b6c925b8f4139d807ac4e4db8575f7dbd2177dd338
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xa8];
    int                  field_a8;
} S0;

extern int zz_027bb54_(int);

int f(S0 *p0)
{
    return zz_027bb54_(p0->field_a8);
}
