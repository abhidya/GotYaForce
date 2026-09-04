/* MATCHED  systemCallbackFunc(MCCSysEvent) @ 0x801819fc  (3 instructions)
 *
 *   801819fc  808dadb4  lwz r4, -0x524c(r13)
 *   80181a00  90640088  stw r3, 0x88(r4)
 *   80181a04  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw blr
 *   exact_bytes      : false
 *   source sha256    : ef39d094cee5874769c014fa9ebcd07325ae6d64cba6bab270df38a480819d0d
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80436354             retail 0x80436354  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80436354 {
    char pad_0[0x88];
    int            field_88;
} G80436354;

extern G80436354 *DAT_80436354;

void f(int p0)
{
    DAT_80436354->field_88 = p0;
}
