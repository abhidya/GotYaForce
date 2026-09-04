/* MATCHED  gnt4-HSD_DObjSetCurrent-bl @ 0x8023d768  (2 instructions)
 *
 *   8023d768  906db30c  stw r3, -0x4cf4(r13)
 *   8023d76c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : fd6caeeaabb6aabdec49e850d7bde4b44d413aad55c457d5826e334a20378784
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804368ac             retail 0x804368ac  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804368ac;

void f(int p0)
{
    DAT_804368ac = p0;
}
