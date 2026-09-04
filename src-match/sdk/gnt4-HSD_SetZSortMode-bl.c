/* MATCHED  gnt4-HSD_SetZSortMode-bl @ 0x8025397c  (3 instructions)
 *
 *   8025397c  906db3fc  stw r3, -0x4c04(r13)
 *   80253980  908db400  stw r4, -0x4c00(r13)
 *   80253984  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : stw stw blr
 *   exact_bytes      : false
 *   source sha256    : a4d88b97d8d468e30d1e5980f7eec173603b69d3fcd4df8e04f00ccd5e63deff
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_8043699c             retail 0x8043699c  (sda, via name-encoded)
 *   +0x004 R_PPC_EMB_SDA21  DAT_804369a0             retail 0x804369a0  (sda, via name-encoded)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_8043699c;
extern int DAT_804369a0;

void f(int p0, int p1)
{
    DAT_8043699c = p0;
    DAT_804369a0 = p1;
}
