/* MATCHED  zz_008d714_ @ 0x8008d714  (4 instructions)
 *
 *   8008d714  800dad14  lwz r0, -0x52ec(r13)
 *   8008d718  906dad14  stw r3, -0x52ec(r13)
 *   8008d71c  7c030378  mr r3, r0
 *   8008d720  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz stw mr blr
 *   exact_bytes      : false
 *   source sha256    : e78c2a841d8abec072661cd54f11a04b17d5f4fbc723d32cf98adeaef7d7084d
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804362b4             retail 0x804362b4  (sda, via registry+name)
 *   +0x004 R_PPC_EMB_SDA21  DAT_804362b4             retail 0x804362b4  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804362b4;

int f(int p0)
{
    int t0;
    t0 = DAT_804362b4;
    DAT_804362b4 = p0;
    return t0;
}
