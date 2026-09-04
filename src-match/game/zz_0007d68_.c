/* MATCHED  zz_0007d68_ @ 0x80007d68  (9 instructions)
 *
 *   80007d68  9421fff0  stwu r1, -0x10(r1)
 *   80007d6c  7c0802a6  mflr r0
 *   80007d70  90010014  stw r0, 0x14(r1)
 *   80007d74  8063000c  lwz r3, 0xc(r3)
 *   80007d78  48001545  bl 0x800092bc
 *   80007d7c  80010014  lwz r0, 0x14(r1)
 *   80007d80  7c0803a6  mtlr r0
 *   80007d84  38210010  addi r1, r1, 0x10
 *   80007d88  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 4468dd871659eb15a28e472292e5d284082c2501d3e7fd4199492143788e3633
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
} S0;

extern int zz_00092bc_(int);

int f(S0 *p0)
{
    return zz_00092bc_(p0->field_c);
}
