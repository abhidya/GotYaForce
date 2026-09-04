/* MATCHED  zz_0010b50_ @ 0x80010b50  (5 instructions)
 *
 *   80010b50  38000000  li r0, 0
 *   80010b54  980dab3c  stb r0, -0x54c4(r13)
 *   80010b58  980dab3a  stb r0, -0x54c6(r13)
 *   80010b5c  b00dab38  sth r0, -0x54c8(r13)
 *   80010b60  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb stb sth blr
 *   exact_bytes      : false
 *   source sha256    : 58e264e81609bbf28106775363a18413800d01c93ada7dabb0c52b37c4c2bd24
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern short DAT_804360d8;
extern char DAT_804360da;
extern char DAT_804360dc;

void f(void)
{
    DAT_804360dc = 0;
    DAT_804360da = 0;
    DAT_804360d8 = 0;
}
