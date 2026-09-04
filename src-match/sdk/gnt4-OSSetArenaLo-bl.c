/* MATCHED  gnt4-OSSetArenaLo-bl @ 0x80200328  (2 instructions)
 *
 *   80200328  906da6c8  stw r3, -0x5938(r13)
 *   8020032c  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw blr
 *   exact_bytes      : false
 *   source sha256    : e9c3a72b7960f9b8b39913c53601c449ea4aa31b9259269439a78d375dc7a832
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80435c68             retail 0x80435c68  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80435c68;

void f(int p0)
{
    DAT_80435c68 = p0;
}
