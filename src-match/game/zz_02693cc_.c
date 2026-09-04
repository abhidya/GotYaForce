/* MATCHED  zz_02693cc_ @ 0x802693cc  (3 instructions)
 *
 *   802693cc  38000000  li r0, 0
 *   802693d0  98030001  stb r0, 1(r3)
 *   802693d4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : true
 *   source sha256    : 0fbfae65739dd3135dde0e9a7c42044138f732a28161696a126d7c0275cf73ee
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x1];
    char           field_1;
} S0;

void f(S0 *p0)
{
    p0->field_1 = 0;
}
