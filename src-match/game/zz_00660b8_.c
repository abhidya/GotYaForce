/* MATCHED  zz_00660b8_ @ 0x800660b8  (4 instructions)
 *
 *   800660b8  8803057b  lbz r0, 0x57b(r3)
 *   800660bc  7c002378  or r0, r0, r4
 *   800660c0  9803057b  stb r0, 0x57b(r3)
 *   800660c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg then permuter (4 mechanical mutants, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 4
 *   shape            : lbz or stb blr
 *   exact_bytes      : true
 *   source sha256    : 9c9379a3b1065042bd4171e65a1a8a4a29d12aa4b555703035fdfc1b55cc7cf7
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x57b];
    unsigned char                 field_57b;
} S0;

void f(S0 *p0, int p1)
{
    p0->field_57b = p0->field_57b | p1;
}
