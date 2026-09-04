/* MATCHED  zz_000df08_ @ 0x8000df08  (8 instructions)
 *
 *   8000df08  38000000  li r0, 0
 *   8000df0c  98030018  stb r0, 0x18(r3)
 *   8000df10  98030019  stb r0, 0x19(r3)
 *   8000df14  9803001a  stb r0, 0x1a(r3)
 *   8000df18  9803001b  stb r0, 0x1b(r3)
 *   8000df1c  9804043d  stb r0, 0x43d(r4)
 *   8000df20  980406f8  stb r0, 0x6f8(r4)
 *   8000df24  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb stb stb stb stb stb blr
 *   exact_bytes      : true
 *   source sha256    : 5dc8a396258a2dd9397d06a267a2cfef097bc84c2f69a25f1c3845a248e8dc94
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x18];
    char           field_18;
    char           field_19;
    char           field_1a;
    char           field_1b;
} S0;

typedef struct S1 {
    char pad_0[0x43d];
    char           field_43d;
    char pad_43e[0x2ba];
    char           field_6f8;
} S1;

void f(S0 *p0, S1 *p1)
{
    p0->field_18 = 0;
    p0->field_19 = 0;
    p0->field_1a = 0;
    p0->field_1b = 0;
    p1->field_43d = 0;
    p1->field_6f8 = 0;
}
