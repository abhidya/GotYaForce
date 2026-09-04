/* MATCHED  zz_018cfd8_ @ 0x8018cfd8  (3 instructions)
 *
 *   8018cfd8  38000000  li r0, 0
 *   8018cfdc  b00306f6  sth r0, 0x6f6(r3)
 *   8018cfe0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li sth blr
 *   exact_bytes      : true
 *   source sha256    : 8fbf57b5763ae5d3ad9c297060b56d709805ff5fe62a2f3138affa87fead205e
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x6f6];
    short          field_6f6;
} S0;

void f(S0 *p0)
{
    p0->field_6f6 = 0;
}
