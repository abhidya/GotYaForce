/* MATCHED  zz_0007c84_ @ 0x80007c84  (10 instructions)
 *
 *   80007c84  9421fff0  stwu r1, -0x10(r1)
 *   80007c88  7c0802a6  mflr r0
 *   80007c8c  38800000  li r4, 0
 *   80007c90  90010014  stw r0, 0x14(r1)
 *   80007c94  8063000c  lwz r3, 0xc(r3)
 *   80007c98  480013d1  bl 0x80009068
 *   80007c9c  80010014  lwz r0, 0x14(r1)
 *   80007ca0  7c0803a6  mtlr r0
 *   80007ca4  38210010  addi r1, r1, 0x10
 *   80007ca8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : c5b2ad4a2aa69d3b29d078af279f29b7c56aa3d14b74a62b6830a5f43403a857
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_0009068_(int, int);

int f(S0 *p0)
{
    return zz_0009068_(p0->field_c, 0);
}
