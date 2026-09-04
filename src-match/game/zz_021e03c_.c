/* MATCHED  zz_021e03c_ @ 0x8021e03c  (2 instructions)
 *
 *   8021e03c  a06db238  lhz r3, -0x4dc8(r13)
 *   8021e040  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lhz blr
 *   exact_bytes      : false
 *   source sha256    : e7ce443c970ac678243cf33c5c81a0975758e0266d2baa1b1bf3ff8851e94e70
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804367d8             retail 0x804367d8  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern unsigned short DAT_804367d8;

unsigned short f(void)
{
    return DAT_804367d8;
}
