/* MATCHED  zz_01a2824_ @ 0x801a2824  (13 instructions)
 *
 *   801a2824  9421fff0  stwu r1, -0x10(r1)
 *   801a2828  7c0802a6  mflr r0
 *   801a282c  90010014  stw r0, 0x14(r1)
 *   801a2830  38000000  li r0, 0
 *   801a2834  9803073f  stb r0, 0x73f(r3)
 *   801a2838  800305e0  lwz r0, 0x5e0(r3)
 *   801a283c  5400003a  rlwinm r0, r0, 0, 0, 0x1d
 *   801a2840  900305e0  stw r0, 0x5e0(r3)
 *   801a2844  4bec7c31  bl 0x8006a474
 *   801a2848  80010014  lwz r0, 0x14(r1)
 *   801a284c  7c0803a6  mtlr r0
 *   801a2850  38210010  addi r1, r1, 0x10
 *   801a2854  4e800020  blr
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
