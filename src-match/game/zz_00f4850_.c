/* MATCHED  zz_00f4850_ @ 0x800f4850  (8 instructions)
 *
 *   800f4850  38000000  li r0, 0
 *   800f4854  b0040014  sth r0, 0x14(r4)
 *   800f4858  b0040012  sth r0, 0x12(r4)
 *   800f485c  b004000c  sth r0, 0xc(r4)
 *   800f4860  b004000a  sth r0, 0xa(r4)
 *   800f4864  98040017  stb r0, 0x17(r4)
 *   800f4868  98040016  stb r0, 0x16(r4)
 *   800f486c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li sth sth sth sth stb stb blr
 *   exact_bytes      : true
 *   source sha256    : fc0ff20e2946118ef545bc7b5c9cd3dd3929d3cc61dca144da19c44005d166f2
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S1 {
    char pad_0[0xa];
    short          field_a;
    short          field_c;
    char pad_e[0x4];
    short          field_12;
    short          field_14;
    char           field_16;
    char           field_17;
} S1;

void f(int p0, S1 *p1)
{
    p1->field_14 = 0;
    p1->field_12 = 0;
    p1->field_c = 0;
    p1->field_a = 0;
    p1->field_17 = 0;
    p1->field_16 = 0;
}
