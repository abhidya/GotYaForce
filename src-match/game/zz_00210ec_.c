/* MATCHED  zz_00210ec_ @ 0x800210ec  (5 instructions)
 *
 *   800210ec  38800002  li r4, 2
 *   800210f0  38000000  li r0, 0
 *   800210f4  988302e4  stb r4, 0x2e4(r3)
 *   800210f8  980302e7  stb r0, 0x2e7(r3)
 *   800210fc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li li stb stb blr
 *   exact_bytes      : true
 *   source sha256    : e365b7cc1f56ab74bc88b05c5738b3df27feaaeb516a38c4ba433ab6522d269e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x2e4];
    char           field_2e4;
    char pad_2e5[0x2];
    char           field_2e7;
} S0;

void f(S0 *p0)
{
    p0->field_2e4 = 2;
    p0->field_2e7 = 0;
}
