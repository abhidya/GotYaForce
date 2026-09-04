/* MATCHED  zz_01b4190_ @ 0x801b4190  (3 instructions)
 *
 *   801b4190  880306e8  lbz r0, 0x6e8(r3)
 *   801b4194  98030144  stb r0, 0x144(r3)
 *   801b4198  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lbz stb blr
 *   exact_bytes      : true
 *   source sha256    : 557b05959adf3dcd8f4e8ceb8cf6b535563cfe4aca4ddea8995e5999a1a8e8b5
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x144];
    unsigned char  field_144;
    char pad_145[0x5a3];
    unsigned char  field_6e8;
} S0;

void f(S0 *p0)
{
    p0->field_144 = p0->field_6e8;
}
