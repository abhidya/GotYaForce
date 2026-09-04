/* MATCHED  zz_019e7d0_ @ 0x8019e7d0  (3 instructions)
 *
 *   8019e7d0  3800ffff  li r0, -1
 *   8019e7d4  980300af  stb r0, 0xaf(r3)
 *   8019e7d8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : true
 *   source sha256    : 439dbf1a842c4b163a2df6436158b1d90173456eea6bafd9dd1d853ed28ac509
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xaf];
    char           field_af;
} S0;

void f(S0 *p0)
{
    p0->field_af = -1;
}
