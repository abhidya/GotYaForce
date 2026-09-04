/* MATCHED  zz_00529ec_ @ 0x800529ec  (4 instructions)
 *
 *   800529ec  806dabf8  lwz r3, -0x5408(r13)
 *   800529f0  38000000  li r0, 0
 *   800529f4  9803000d  stb r0, 0xd(r3)
 *   800529f8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li stb blr
 *   exact_bytes      : false
 *   source sha256    : 1a403eb5cce06bb778acdd7fd3d70b469b3d416be9a38c53499acc6635db9cb3
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80436198             retail 0x80436198  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80436198 {
    char pad_0[0xd];
    char           field_d;
} G80436198;

extern G80436198 *DAT_80436198;

void f(void)
{
    DAT_80436198->field_d = 0;
}
