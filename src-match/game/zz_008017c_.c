/* MATCHED  zz_008017c_ @ 0x8008017c  (2 instructions)
 *
 *   8008017c  806dac14  lwz r3, -0x53ec(r13)
 *   80080180  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : f5caafc4e2065535e35c6fe9a3fcf9d09e8edbde8b331bf64fad4db4bc1e4eed
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804361b4             retail 0x804361b4  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361b4;

int f(void)
{
    return DAT_804361b4;
}
