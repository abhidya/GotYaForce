/* MATCHED  gnt4-HSD_AObjInitEndCallBack @ 0x80243b24  (4 instructions)
 *
 *   80243b24  38000000  li r0, 0
 *   80243b28  900db390  stw r0, -0x4c70(r13)
 *   80243b2c  900db38c  stw r0, -0x4c74(r13)
 *   80243b30  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 6fac78f8c9eec99e449362a92288b728c0d7de7f1d137cd8cadf183084344b4b
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_80436930             retail 0x80436930  (sda, via name-encoded)
 *   +0x008 R_PPC_EMB_SDA21  DAT_8043692c             retail 0x8043692c  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043692c;
extern int DAT_80436930;

void f(void)
{
    DAT_80436930 = 0;
    DAT_8043692c = 0;
}
