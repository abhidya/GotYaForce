/* MATCHED  cPlayer::ClearSwapControllerTimer(void) @ 0x802807ac  (6 instructions)
 *
 *   802807ac  38000000  li r0, 0
 *   802807b0  90030010  stw r0, 0x10(r3)
 *   802807b4  90030014  stw r0, 0x14(r3)
 *   802807b8  90030018  stw r0, 0x18(r3)
 *   802807bc  9003001c  stw r0, 0x1c(r3)
 *   802807c0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw stw blr
 *   exact_bytes      : true
 *   source sha256    : 1e243afab742cd5cb93d852474312d0505c778408bf4a0b6b0f133d42a680162
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x10];
    int            field_10;
    int            field_14;
    int            field_18;
    int            field_1c;
} S0;

void f(S0 *p0)
{
    p0->field_10 = 0;
    p0->field_14 = 0;
    p0->field_18 = 0;
    p0->field_1c = 0;
}
