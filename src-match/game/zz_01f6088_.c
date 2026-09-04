/* MATCHED  zz_01f6088_ @ 0x801f6088  (4 instructions)
 *
 *   801f6088  806dae10  lwz r3, -0x51f0(r13)
 *   801f608c  88630008  lbz r3, 8(r3)
 *   801f6090  7c630774  extsb r3, r3
 *   801f6094  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lbz extsb blr
 *   exact_bytes      : false
 *   source sha256    : ef0e10d86188e4c69e5940b366369d0afc1a3a7f741fe375f020b5b5a490f456
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804363b0             retail 0x804363b0  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G804363b0 {
    char pad_0[0x8];
    char           field_8;
} G804363b0;

extern G804363b0 *DAT_804363b0;

int f(void)
{
    return DAT_804363b0->field_8;
}
