/* MATCHED  zz_00d602c_ @ 0x800d602c  (3 instructions)
 *
 *   800d602c  8063008c  lwz r3, 0x8c(r3)
 *   800d6030  80630170  lwz r3, 0x170(r3)
 *   800d6034  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lwz blr
 *   exact_bytes      : true
 *   source sha256    : 5f8f2413b9276beb82b04da96b339377c112d68ca65d1085cac8b1e428ec8d26
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0_8c {
    char pad_0[0x170];
    int                  field_170;
} S0_8c;

typedef struct S0 {
    char pad_0[0x8c];
    S0_8c *              field_8c;
} S0;

int f(S0 *p0)
{
    return p0->field_8c->field_170;
}
