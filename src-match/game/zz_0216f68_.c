/* MATCHED  zz_0216f68_ @ 0x80216f68  (4 instructions)
 *
 *   80216f68  800db110  lwz r0, -0x4ef0(r13)
 *   80216f6c  90030008  stw r0, 8(r3)
 *   80216f70  906db110  stw r3, -0x4ef0(r13)
 *   80216f74  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 1e6635c6902af74213ac94a4a92890d1de4707a388ef3e61c2b7aaec1536391c
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804366b0             retail 0x804366b0  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_804366b0             retail 0x804366b0  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct S0 {
    char pad_0[0x8];
    int            field_8;
} S0;

extern int DAT_804366b0;

void f(S0 *p0)
{
    p0->field_8 = DAT_804366b0;
    DAT_804366b0 = p0;
}
