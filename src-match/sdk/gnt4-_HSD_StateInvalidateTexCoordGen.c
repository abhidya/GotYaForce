/* MATCHED  gnt4-_HSD_StateInvalidateTexCoordGen @ 0x80242298  (3 instructions)
 *
 *   80242298  38000000  li r0, 0
 *   8024229c  900db358  stw r0, -0x4ca8(r13)
 *   802422a0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : bb02fbaff76155433adc4743e6bda05a392fdde2a0746937a24470cd83eceb88
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_804368f8             retail 0x804368f8  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368f8;

void f(void)
{
    DAT_804368f8 = 0;
}
