/* MATCHED  zz_004060c_ @ 0x8004060c  (4 instructions)
 *
 *   8004060c  806d8398  lwz r3, -0x7c68(r13)
 *   80040610  38000000  li r0, 0
 *   80040614  98030003  stb r0, 3(r3)
 *   80040618  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li stb blr
 *   exact_bytes      : false
 *   source sha256    : 21f130fdadc719c2ab5c6a8fb9c9cf6152cfd73b93070af0a764cca4ed8925f5
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  PTR_DAT_80433938         retail 0x80433938  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80433938 {
    char pad_0[0x3];
    char           field_3;
} G80433938;

extern G80433938 *PTR_DAT_80433938;

void f(void)
{
    PTR_DAT_80433938->field_3 = 0;
}
