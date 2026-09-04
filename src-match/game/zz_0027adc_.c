/* MATCHED  zz_0027adc_ @ 0x80027adc  (3 instructions)
 *
 *   80027adc  806dab6c  lwz r3, -0x5494(r13)
 *   80027ae0  a8630004  lha r3, 4(r3)
 *   80027ae4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lha blr
 *   exact_bytes      : false
 *   source sha256    : 442847a84978844ef142516a54a0112e849bb3e1cdf83d517c6f769c7eb2190e
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_8043610c             retail 0x8043610c  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G8043610c {
    char pad_0[0x4];
    short          field_4;
} G8043610c;

extern G8043610c *DAT_8043610c;

short f(void)
{
    return DAT_8043610c->field_4;
}
