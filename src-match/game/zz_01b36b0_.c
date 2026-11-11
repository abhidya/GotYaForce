/* MATCHED  zz_01b36b0_ @ 0x801b36b0  (13 instructions)
 *
 *   801b36b0  9421fff0  stwu r1, -0x10(r1)
 *   801b36b4  7c0802a6  mflr r0
 *   801b36b8  90010014  stw r0, 0x14(r1)
 *   801b36bc  800305e0  lwz r0, 0x5e0(r3)
 *   801b36c0  540006f7  rlwinm. r0, r0, 0, 0x1b, 0x1b
 *   801b36c4  41820010  beq 0x801b36d4
 *   801b36c8  38800014  li r4, 0x14
 *   801b36cc  38a00006  li r5, 6
 *   801b36d0  4bf3ca35  bl 0x800f0104
 *   801b36d4  80010014  lwz r0, 0x14(r1)
 *   801b36d8  7c0803a6  mtlr r0
 *   801b36dc  38210010  addi r1, r1, 0x10
 *   801b36e0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw lwz rlwinm. beq li li bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : 0296381ac5e3e94b2be7fd957dbadbe6276c6bd5cf2ef20c654f442957570a3a
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x5e0];
    int                  field_5e0;
} S0;

extern int zz_00f0104_(int, int, int);

void f(S0 *p0)
{
    if ((p0->field_5e0 & 0x10) != 0)
        zz_00f0104_(p0, 0x14, 6);
}
