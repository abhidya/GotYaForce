/* MATCHED  gnt4-DVDSetAutoInvalidation @ 0x8020f8c8  (4 instructions)
 *
 *   8020f8c8  800da71c  lwz r0, -0x58e4(r13)
 *   8020f8cc  906da71c  stw r3, -0x58e4(r13)
 *   8020f8d0  7c030378  mr r3, r0
 *   8020f8d4  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw mr blr
 *   exact_bytes      : false
 *   source sha256    : 4f030f42ecdff92713afbc2611600b8363e806c44852db2c7e80697cb5656b3f
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80435cbc             retail 0x80435cbc  (sda, via name-encoded)
 *   +0x004 R_PPC_EMB_SDA21  DAT_80435cbc             retail 0x80435cbc  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80435cbc;

int f(int p0)
{
    int t0;
    t0 = DAT_80435cbc;
    DAT_80435cbc = p0;
    return t0;
}
