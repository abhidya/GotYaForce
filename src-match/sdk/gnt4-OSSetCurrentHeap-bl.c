/* MATCHED  gnt4-OSSetCurrentHeap-bl @ 0x801ffeb0  (4 instructions)
 *
 *   801ffeb0  800da6c0  lwz r0, -0x5940(r13)
 *   801ffeb4  906da6c0  stw r3, -0x5940(r13)
 *   801ffeb8  7c030378  mr r3, r0
 *   801ffebc  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw mr blr
 *   exact_bytes      : false
 *   source sha256    : afb828fa45415a29989c69fd195806bfe6e9f0ea9ba2c2b7a88e78476f9d0b29
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80435c60             retail 0x80435c60  (sda, via registry+name)
 *   +0x004 R_PPC_EMB_SDA21  DAT_80435c60             retail 0x80435c60  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80435c60;

int f(int p0)
{
    int t0;
    t0 = DAT_80435c60;
    DAT_80435c60 = p0;
    return t0;
}
