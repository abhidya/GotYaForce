/* MATCHED  InstallCallStackDumper(void) @ 0x8029aa70  (11 instructions)
 *
 *   8029aa70  9421fff0  stwu r1, -0x10(r1)
 *   8029aa74  7c0802a6  mflr r0
 *   8029aa78  3c808042  lis r4, -0x7fbe
 *   8029aa7c  38600020  li r3, 0x20
 *   8029aa80  90010014  stw r0, 0x14(r1)
 *   8029aa84  3884d018  addi r4, r4, -0x2fe8
 *   8029aa88  4800e7bd  bl 0x802a9244
 *   8029aa8c  80010014  lwz r0, 0x14(r1)
 *   8029aa90  7c0803a6  mtlr r0
 *   8029aa94  38210010  addi r1, r1, 0x10
 *   8029aa98  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr lis li stw addi bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 969a9bc44002dc38d7499ebe55cd3353628a00bfb2a065b1fd5505dc0384e205
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern struct { int v; char pad_[8]; } DAT_8041d018;

extern int zz_02a9244_(int, int);

int f(void)
{
    return zz_02a9244_(0x20, &DAT_8041d018);
}
