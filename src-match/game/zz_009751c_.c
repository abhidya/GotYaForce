/* MATCHED  zz_009751c_ @ 0x8009751c  (4 instructions)
 *
 *   8009751c  38000000  li r0, 0
 *   80097520  900dad88  stw r0, -0x5278(r13)
 *   80097524  900dad7c  stw r0, -0x5284(r13)
 *   80097528  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 832f0722e95792bb07e6fa9d4bef7f8dea3dc77734216a7b000e8e99fb6f4efb
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_80436328             retail 0x80436328  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_8043631c             retail 0x8043631c  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043631c;
extern int DAT_80436328;

void f(void)
{
    DAT_80436328 = 0;
    DAT_8043631c = 0;
}
