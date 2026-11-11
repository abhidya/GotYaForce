/* MATCHED  zz_01c13b0_ @ 0x801c13b0  (6 instructions)
 *
 *   801c13b0  800305e0  lwz r0, 0x5e0(r3)
 *   801c13b4  54000673  rlwinm. r0, r0, 0, 0x19, 0x19
 *   801c13b8  4c820020  bnelr
 *   801c13bc  38000000  li r0, 0
 *   801c13c0  98031d98  stb r0, 0x1d98(r3)
 *   801c13c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz rlwinm. bnelr li stb blr
 *   exact_bytes      : true
 *   source sha256    : 274b871d67faaaf419955871d8914e1fabdfe669e8f0c443693ea84664610341
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x5e0];
    int                  field_5e0;
    char pad_5e4[0x17b4];
    char                 field_1d98;
} S0;

void f(S0 *p0)
{
    if ((p0->field_5e0 & 0x40) != 0)
        return;
    p0->field_1d98 = 0;
}
