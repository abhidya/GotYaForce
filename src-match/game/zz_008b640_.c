/* MATCHED  zz_008b640_ @ 0x8008b640  (4 instructions)
 *
 *   8008b640  806d8394  lwz r3, -0x7c6c(r13)
 *   8008b644  38000001  li r0, 1
 *   8008b648  b00300e8  sth r0, 0xe8(r3)
 *   8008b64c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li sth blr
 *   exact_bytes      : false
 *   source sha256    : 2d802871981a533133ad37612511904b9d0a1141985f412ebb7684af18404c26
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
    char pad_0[0xe8];
    short          field_e8;
} G80433934;

extern G80433934 *PTR_DAT_80433934;

void f(void)
{
    PTR_DAT_80433934->field_e8 = 1;
}
