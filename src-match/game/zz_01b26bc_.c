/* MATCHED  zz_01b26bc_ @ 0x801b26bc  (3 instructions)
 *
 *   801b26bc  38000001  li r0, 1
 *   801b26c0  98030144  stb r0, 0x144(r3)
 *   801b26c4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/leaf (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : true
 *   source sha256    : 5bfba895295586783636af7f1fde32ea66ae051f4fab6e8d8e1f8c7999cf9d5f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x144];
    char           field_144;
} S0;

void f(S0 *p0)
{
    p0->field_144 = 1;
}
