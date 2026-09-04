/* MATCHED  zz_021e03c_ @ 0x8021e03c  (2 instructions)
 *
 *   8021e03c  a06db238  lhz r3, -0x4dc8(r13)
 *   8021e040  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/loop.py.
 *   candidate source : seed/cfg (iteration 0, no model call)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lhz blr
 *   exact_bytes      : false
 *   source sha256    : 93c90482caadf41e201a7f11bae4210694bf7844646e9d2df27e8f10b3a646cc
 *
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern unsigned short DAT_804367d8;

int f(void)
{
    return DAT_804367d8;
}
