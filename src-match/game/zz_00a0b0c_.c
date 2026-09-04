/* MATCHED  zz_00a0b0c_ @ 0x800a0b0c  (10 instructions)
 *
 *   800a0b0c  9421fff0  stwu r1, -0x10(r1)
 *   800a0b10  7c0802a6  mflr r0
 *   800a0b14  38800001  li r4, 1
 *   800a0b18  90010014  stw r0, 0x14(r1)
 *   800a0b1c  80630144  lwz r3, 0x144(r3)
 *   800a0b20  4bf68e39  bl 0x80009958
 *   800a0b24  80010014  lwz r0, 0x14(r1)
 *   800a0b28  7c0803a6  mtlr r0
 *   800a0b2c  38210010  addi r1, r1, 0x10
 *   800a0b30  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr li stw lwz bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 980a1791d9dcd5be20cbf7fe5c00dc9a35564b993e2f50dde4674e6fd28703ee
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x144];
    int                  field_144;
} S0;

extern int zz_0009958_(int, int);

int f(S0 *p0)
{
    return zz_0009958_(p0->field_144, 1);
}
