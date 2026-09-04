/* MATCHED  zz_016e368_ @ 0x8016e368  (5 instructions)
 *
 *   8016e368  38800003  li r4, 3
 *   8016e36c  38000000  li r0, 0
 *   8016e370  98830018  stb r4, 0x18(r3)
 *   8016e374  98030082  stb r0, 0x82(r3)
 *   8016e378  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li li stb stb blr
 *   exact_bytes      : true
 *   source sha256    : 2e74116c356252eab9965064528c4a612d466d9f3708b2ebd58df75547808a7d
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x18];
    char           field_18;
    char pad_19[0x69];
    char           field_82;
} S0;

void f(S0 *p0)
{
    p0->field_18 = 3;
    p0->field_82 = 0;
}
