/* MATCHED  zz_00f1d88_ @ 0x800f1d88  (3 instructions)
 *
 *   800f1d88  38000007  li r0, 7
 *   800f1d8c  98030089  stb r0, 0x89(r3)
 *   800f1d90  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : true
 *   source sha256    : 2d389296a27e3e83a71dcbe87f3ab415752a2cd0d383bbf07b6407cd5feb19d9
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x89];
    char           field_89;
} S0;

void f(S0 *p0)
{
    p0->field_89 = 7;
}
