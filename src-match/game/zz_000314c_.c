/* MATCHED  zz_000314c_ @ 0x8000314c  (2 instructions)
 *
 *   8000314c  886daef8  lbz r3, -0x5108(r13)
 *   80003150  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lbz blr
 *   exact_bytes      : false
 *   source sha256    : b3c73b1aae1058b5ec9c59488282c9fad75e1bbbf2e04c3f8a9cab93df3aa448
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80436498             retail 0x80436498  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern unsigned char DAT_80436498;

unsigned char f(void)
{
    return DAT_80436498;
}
