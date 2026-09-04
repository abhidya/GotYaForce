/* MATCHED  gnt4-GXClearGPMetric-bl @ 0x8022cae8  (4 instructions)
 *
 *   8022cae8  806db244  lwz r3, -0x4dbc(r13)
 *   8022caec  38000004  li r0, 4
 *   8022caf0  b0030004  sth r0, 4(r3)
 *   8022caf4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li sth blr
 *   exact_bytes      : false
 *   source sha256    : 383b082a380979231f39d86c65ccb5011805209b28cb4209bdb7854181a41ea5
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804367e4             retail 0x804367e4  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G804367e4 {
    char pad_0[0x4];
    short          field_4;
} G804367e4;

extern G804367e4 *DAT_804367e4;

void f(void)
{
    DAT_804367e4->field_4 = 4;
}
