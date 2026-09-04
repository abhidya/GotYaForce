/* MATCHED  zz_008c088_ @ 0x8008c088  (4 instructions)
 *
 *   8008c088  38000000  li r0, 0
 *   8008c08c  900dac48  stw r0, -0x53b8(r13)
 *   8008c090  900dac38  stw r0, -0x53c8(r13)
 *   8008c094  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : b48449a08e5a78b320fd7ce9c5e76879f666f086b1e0d39ba0995f3bdca68a9f
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_804361e8             retail 0x804361e8  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_804361d8             retail 0x804361d8  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
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
