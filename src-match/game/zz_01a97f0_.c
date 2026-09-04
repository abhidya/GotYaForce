/* MATCHED  zz_01a97f0_ @ 0x801a97f0  (5 instructions)
 *
 *   801a97f0  38800003  li r4, 3
 *   801a97f4  38000000  li r0, 0
 *   801a97f8  98830018  stb r4, 0x18(r3)
 *   801a97fc  98030082  stb r0, 0x82(r3)
 *   801a9800  4e800020  blr
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
