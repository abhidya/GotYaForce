/* MATCHED  gnt4-GXGetGPFifo-bl @ 0x8022588c  (2 instructions)
 *
 *   8022588c  806db26c  lwz r3, -0x4d94(r13)
 *   80225890  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz blr
 *   exact_bytes      : false
 *   source sha256    : 4687038ef6f22fa1625622edb24a9b8ae807e7ab94dc16956b08864391dfa16c
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_8043680c             retail 0x8043680c  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043680c;

int f(void)
{
    return DAT_8043680c;
}
