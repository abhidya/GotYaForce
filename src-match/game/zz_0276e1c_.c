/* MATCHED  zz_0276e1c_ @ 0x80276e1c  (2 instructions)
 *
 *   80276e1c  80630020  lwz r3, 0x20(r3)
 *   80276e20  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : true
 *   source sha256    : 34fd4bdcc4c94edc5dd26f38470b50723d1533ee6d77afae320d30f9ce234b97
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x20];
    int            field_20;
} S0;

int f(S0 *p0)
{
    return p0->field_20;
}
