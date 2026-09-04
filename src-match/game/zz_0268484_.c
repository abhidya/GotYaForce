/* MATCHED  zz_0268484_ @ 0x80268484  (3 instructions)
 *
 *   80268484  90830078  stw r4, 0x78(r3)
 *   80268488  90a3007c  stw r5, 0x7c(r3)
 *   8026848c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 5443afc07f4bfd792c1d4dc07bad548be5f73f03da42a84bbcef313521d15a91
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x78];
    int            field_78;
    int            field_7c;
} S0;

void f(S0 *p0, int p1, int p2)
{
    p0->field_78 = p1;
    p0->field_7c = p2;
}
