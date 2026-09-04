/* MATCHED  zz_01bfbe4_ @ 0x801bfbe4  (4 instructions)
 *
 *   801bfbe4  806da490  lwz r3, -0x5b70(r13)
 *   801bfbe8  38000000  li r0, 0
 *   801bfbec  90030154  stw r0, 0x154(r3)
 *   801bfbf0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li stw blr
 *   exact_bytes      : false
 *   source sha256    : 58107bb6aa4ca2cca56aec147be6521acc195bccfbb946f5a279f1572e9b1318
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  PTR_DAT_80435a30         retail 0x80435a30  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80435a30 {
    char pad_0[0x154];
    int            field_154;
} G80435a30;

extern G80435a30 *PTR_DAT_80435a30;

void f(void)
{
    PTR_DAT_80435a30->field_154 = 0;
}
