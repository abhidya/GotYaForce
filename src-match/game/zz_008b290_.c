/* MATCHED  zz_008b290_ @ 0x8008b290  (3 instructions)
 *
 *   8008b290  806d8394  lwz r3, -0x7c6c(r13)
 *   8008b294  886300d9  lbz r3, 0xd9(r3)
 *   8008b298  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lbz blr
 *   exact_bytes      : false
 *   source sha256    : 907456a494ef786c08ce94e46f589f05a4069935f7849661810909d62d828a9e
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  PTR_DAT_80433934         retail 0x80433934  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80433934 {
    char pad_0[0xd9];
    unsigned char  field_d9;
} G80433934;

extern G80433934 *PTR_DAT_80433934;

unsigned char f(void)
{
    return PTR_DAT_80433934->field_d9;
}
