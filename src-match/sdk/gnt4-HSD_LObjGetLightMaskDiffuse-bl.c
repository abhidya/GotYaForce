/* MATCHED  gnt4-HSD_LObjGetLightMaskDiffuse-bl @ 0x80243ffc  (2 instructions)
 *
 *   80243ffc  806db3a4  lwz r3, -0x4c5c(r13)
 *   80244000  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 6fb2361c06c7fb34ca4cec079da33c24ada91a6c264810cb1279ca56742cf3e3
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80436944             retail 0x80436944  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436944;

int f(void)
{
    return DAT_80436944;
}
