/* MATCHED  zz_002590c_ @ 0x8002590c  (14 instructions)
 *
 *   8002590c  a88301c4  lha r4, 0x1c4(r3)
 *   80025910  a80301c6  lha r0, 0x1c6(r3)
 *   80025914  7c040000  cmpw r4, r0
 *   80025918  4082001c  bne 0x80025934
 *   8002591c  a80306b8  lha r0, 0x6b8(r3)
 *   80025920  2c000000  cmpwi r0, 0
 *   80025924  40820010  bne 0x80025934
 *   80025928  a80306ba  lha r0, 0x6ba(r3)
 *   8002592c  2c000000  cmpwi r0, 0
 *   80025930  4182000c  beq 0x8002593c
 *   80025934  38600001  li r3, 1
 *   80025938  4e800020  blr
 *   8002593c  38600000  li r3, 0
 *   80025940  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lha lha cmpw bne lha cmpwi bne lha cmpwi beq li blr li blr
 *   exact_bytes      : true
 *   source sha256    : 02670b9a821d6adde2991888cb3ef2320476d712c5669b32d9def6c1a21f70ad
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x1c4];
    short                field_1c4;
    short                field_1c6;
    char pad_1c8[0x4f0];
    short                field_6b8;
    short                field_6ba;
} S0;

int f(S0 *p0)
{
    if (p0->field_1c4 != p0->field_1c6 || p0->field_6b8 != 0 || p0->field_6ba != 0)
        return 1;
    return 0;
}
