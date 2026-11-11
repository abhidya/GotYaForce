/* MATCHED  zz_01b56d4_ @ 0x801b56d4  (13 instructions)
 *
 *   801b56d4  9421fff0  stwu r1, -0x10(r1)
 *   801b56d8  7c0802a6  mflr r0
 *   801b56dc  90010014  stw r0, 0x14(r1)
 *   801b56e0  38000000  li r0, 0
 *   801b56e4  9803073f  stb r0, 0x73f(r3)
 *   801b56e8  800305e0  lwz r0, 0x5e0(r3)
 *   801b56ec  5400003a  rlwinm r0, r0, 0, 0, 0x1d
 *   801b56f0  900305e0  stw r0, 0x5e0(r3)
 *   801b56f4  4beb4d81  bl 0x8006a474
 *   801b56f8  80010014  lwz r0, 0x14(r1)
 *   801b56fc  7c0803a6  mtlr r0
 *   801b5700  38210010  addi r1, r1, 0x10
 *   801b5704  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stwu mflr stw li stb lwz rlwinm stw bl lwz mtlr addi blr
 *   exact_bytes      : false
 *   source sha256    : a45b91fd56a0bb4a937364a72bf3a073345a50681b4bd488f2f53de621be2e66
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x5e0];
    int                  field_5e0;
    char pad_5e4[0x15b];
    char                 field_73f;
} S0;

extern int zz_006a474_(void);

int f(S0 *p0)
{
    p0->field_73f = 0;
    p0->field_5e0 = p0->field_5e0 & 0xfffffffc;
    return zz_006a474_();
}
