/* MATCHED  zz_0225884_ @ 0x80225884  (2 instructions)
 *
 *   80225884  806db268  lwz r3, -0x4d98(r13)
 *   80225888  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 03e835fd09a9df07cde8555ecb4773410187b318e7a076f9a6a4406813115dd1
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80436808             retail 0x80436808  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436808;

int f(void)
{
    return DAT_80436808;
}
