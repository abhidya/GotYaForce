/* MATCHED  gnt4-_HSD_StateInvalidateTevStage @ 0x8024226c  (3 instructions)
 *
 *   8024226c  38000000  li r0, 0
 *   80242270  900db370  stw r0, -0x4c90(r13)
 *   80242274  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : e82a0260dbedbc2cb3a94aa5c0e76803b53d70de4b56604277751c1dfb56fd76
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_80436910             retail 0x80436910  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436910;

void f(void)
{
    DAT_80436910 = 0;
}
