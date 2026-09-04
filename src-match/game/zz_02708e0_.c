/* MATCHED  zz_02708e0_ @ 0x802708e0  (13 instructions)
 *
 *   802708e0  8003000c  lwz r0, 0xc(r3)
 *   802708e4  2c000000  cmpwi r0, 0
 *   802708e8  40820024  bne 0x8027090c
 *   802708ec  38000002  li r0, 2
 *   802708f0  90030014  stw r0, 0x14(r3)
 *   802708f4  90830018  stw r4, 0x18(r3)
 *   802708f8  90a3001c  stw r5, 0x1c(r3)
 *   802708fc  90c30020  stw r6, 0x20(r3)
 *   80270900  90e30024  stw r7, 0x24(r3)
 *   80270904  38600001  li r3, 1
 *   80270908  4e800020  blr
 *   8027090c  38600000  li r3, 0
 *   80270910  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz cmpwi bne li stw stw stw stw stw li blr li blr
 *   exact_bytes      : true
 *   source sha256    : e78a64e170ac4839ff77b6a9a8b0e8a0fc07ea654c9ed76ce0693db1f5b07889
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0xc];
    int                  field_c;
    char pad_10[0x4];
    int                  field_14;
    int                  field_18;
    int                  field_1c;
    int                  field_20;
    int                  field_24;
} S0;

int f(S0 *p0, int p1, int p2, int p3, int p4)
{
    if (p0->field_c == 0)
    {
        p0->field_14 = 2;
        p0->field_18 = p1;
        p0->field_1c = p2;
        p0->field_20 = p3;
        p0->field_24 = p4;
        return 1;
    }
    return 0;
}
