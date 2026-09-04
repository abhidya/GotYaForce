/* MATCHED  zz_01f6098_ @ 0x801f6098  (3 instructions)
 *
 *   801f6098  808dae10  lwz r4, -0x51f0(r13)
 *   801f609c  98640008  stb r3, 8(r4)
 *   801f60a0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stb blr
 *   exact_bytes      : false
 *   source sha256    : 91fb525b40aa4e57dcd44f4234b345d71777b7e404e714ba31a38375e28f1305
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

void f(int p0)
{
    DAT_804363b0->field_8 = p0;
}
