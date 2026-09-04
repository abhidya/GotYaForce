/* MATCHED  gnt4-HSD_LObjSetColor @ 0x80245a74  (3 instructions)
 *
 *   80245a74  80040000  lwz r0, 0(r4)
 *   80245a78  90030010  stw r0, 0x10(r3)
 *   80245a7c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw blr
 *   exact_bytes      : true
 *   source sha256    : 8529604e8c554064048b5b5ff5bfcd00a2b2792293bc9b45db88e452e3a18794
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x10];
    int            field_10;
} S0;

typedef struct S1 {
    int            field_0;
} S1;

void f(S0 *p0, S1 *p1)
{
    p0->field_10 = p1->field_0;
}
