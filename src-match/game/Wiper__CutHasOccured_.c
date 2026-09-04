/* MATCHED  Wiper::CutHasOccured( @ 0x80052da8  (3 instructions)
 *
 *   80052da8  806dabf8  lwz r3, -0x5408(r13)
 *   80052dac  88630005  lbz r3, 5(r3)
 *   80052db0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz lbz blr
 *   exact_bytes      : false
 *   source sha256    : c4288a512fa85a76913a0381e47c754f1e49c607c3a1c765949768ec814fc2ef
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_80436198             retail 0x80436198  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80436198 {
    char pad_0[0x5];
    unsigned char  field_5;
} G80436198;

extern G80436198 *DAT_80436198;

unsigned char f(void)
{
    return DAT_80436198->field_5;
}
