/* MATCHED  zz_008c3a0_ @ 0x8008c3a0  (3 instructions)
 *
 *   8008c3a0  808d8390  lwz r4, -0x7c70(r13)
 *   8008c3a4  9864003e  stb r3, 0x3e(r4)
 *   8008c3a8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stb blr
 *   exact_bytes      : false
 *   source sha256    : bc974d5691e88d97dee18329cb52151d3f503b91aff0156c9d8d103b7a2b700e
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  PTR_DAT_80433930         retail 0x80433930  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80433930 {
    char pad_0[0x3e];
    char           field_3e;
} G80433930;

extern G80433930 *PTR_DAT_80433930;

void f(int p0)
{
    PTR_DAT_80433930->field_3e = p0;
}
