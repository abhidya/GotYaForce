/* MATCHED  zz_00b2d24_ @ 0x800b2d24  (14 instructions)
 *
 *   800b2d24  38000000  li r0, 0
 *   800b2d28  b0040016  sth r0, 0x16(r4)
 *   800b2d2c  b0040014  sth r0, 0x14(r4)
 *   800b2d30  b0040012  sth r0, 0x12(r4)
 *   800b2d34  b0040010  sth r0, 0x10(r4)
 *   800b2d38  b0040006  sth r0, 6(r4)
 *   800b2d3c  b0040004  sth r0, 4(r4)
 *   800b2d40  b0040002  sth r0, 2(r4)
 *   800b2d44  b0040000  sth r0, 0(r4)
 *   800b2d48  9804001b  stb r0, 0x1b(r4)
 *   800b2d4c  9804001a  stb r0, 0x1a(r4)
 *   800b2d50  98040019  stb r0, 0x19(r4)
 *   800b2d54  98040018  stb r0, 0x18(r4)
 *   800b2d58  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li sth sth sth sth sth sth sth sth stb stb stb stb blr
 *   exact_bytes      : true
 *   source sha256    : 9c8f2f04add5dd225488ea48a5f18902859f5c1bd6a2d6bc3ffe730b686b31c4
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S1 {
    short          field_0;
    short          field_2;
    short          field_4;
    short          field_6;
    char pad_8[0x8];
    short          field_10;
    short          field_12;
    short          field_14;
    short          field_16;
    char           field_18;
    char           field_19;
    char           field_1a;
    char           field_1b;
} S1;

void f(int p0, S1 *p1)
{
    p1->field_16 = 0;
    p1->field_14 = 0;
    p1->field_12 = 0;
    p1->field_10 = 0;
    p1->field_6 = 0;
    p1->field_4 = 0;
    p1->field_2 = 0;
    p1->field_0 = 0;
    p1->field_1b = 0;
    p1->field_1a = 0;
    p1->field_19 = 0;
    p1->field_18 = 0;
}
