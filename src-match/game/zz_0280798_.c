/* MATCHED  zz_0280798_ @ 0x80280798  (5 instructions)
 *
 *   80280798  38000400  li r0, 0x400
 *   8028079c  900302ec  stw r0, 0x2ec(r3)
 *   802807a0  900302f4  stw r0, 0x2f4(r3)
 *   802807a4  900302f0  stw r0, 0x2f0(r3)
 *   802807a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw blr
 *   exact_bytes      : true
 *   source sha256    : ed92c8358fc8d48c9a5066d06a4929ba46e6fa0c2836d1b41598cc55cd2f1d26
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x2ec];
    int            field_2ec;
    int            field_2f0;
    int            field_2f4;
} S0;

void f(S0 *p0)
{
    p0->field_2ec = 0x400;
    p0->field_2f4 = 0x400;
    p0->field_2f0 = 0x400;
}
