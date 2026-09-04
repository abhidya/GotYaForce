/* MATCHED  zz_0007d18_ @ 0x80007d18  (10 instructions)
 *
 *   80007d18  9421fff0  stwu r1, -0x10(r1)
 *   80007d1c  7c0802a6  mflr r0
 *   80007d20  38800008  li r4, 8
 *   80007d24  90010014  stw r0, 0x14(r1)
 *   80007d28  8063000c  lwz r3, 0xc(r3)
 *   80007d2c  48245845  bl 0x8024d570
 *   80007d30  80010014  lwz r0, 0x14(r1)
 *   80007d34  7c0803a6  mtlr r0
 *   80007d38  38210010  addi r1, r1, 0x10
 *   80007d3c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : fd08d938837675495035ff3caf6c747dd1cfd8a52f9a18cb5e23faa4689cad14
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
    return zz_024d570_(p0->field_c, 8);
}
