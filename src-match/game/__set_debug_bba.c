/* MATCHED  __set_debug_bba @ 0x80003140  (3 instructions)
 *
 *   80003140  38000001  li r0, 1
 *   80003144  980daef8  stb r0, -0x5108(r13)
 *   80003148  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb blr
 *   exact_bytes      : false
 *   source sha256    : 5d60a441d0d640f79a27f50fbb063af39b263abec979b27668c0b2f75ceca463
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_80436498             retail 0x80436498  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern char DAT_80436498;

void f(void)
{
    DAT_80436498 = 1;
}
