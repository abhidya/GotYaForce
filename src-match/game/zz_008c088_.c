/* MATCHED  zz_008c088_ @ 0x8008c088  (4 instructions)
 *
 *   8008c088  38000000  li r0, 0
 *   8008c08c  900dac48  stw r0, -0x53b8(r13)
 *   8008c090  900dac38  stw r0, -0x53c8(r13)
 *   8008c094  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : b48449a08e5a78b320fd7ce9c5e76879f666f086b1e0d39ba0995f3bdca68a9f
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361d8;
extern int DAT_804361e8;

void f(void)
{
    DAT_804361e8 = 0;
    DAT_804361d8 = 0;
}
