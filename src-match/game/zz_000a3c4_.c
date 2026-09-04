/* MATCHED  zz_000a3c4_ @ 0x8000a3c4  (4 instructions)
 *
 *   8000a3c4  806dab30  lwz r3, -0x54d0(r13)
 *   8000a3c8  88630000  lbz r3, 0(r3)
 *   8000a3cc  7c630774  extsb r3, r3
 *   8000a3d0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lbz extsb blr
 *   exact_bytes      : false
 *   source sha256    : 7b9e6eb8fd8faa183e5f354c695a35e41bddf59a5d4529e75efc87b150f1e8c1
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804360d0             retail 0x804360d0  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G804360d0 {
    char           field_0;
} G804360d0;

extern G804360d0 *DAT_804360d0;

int f(void)
{
    return DAT_804360d0->field_0;
}
