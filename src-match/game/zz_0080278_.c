/* MATCHED  zz_0080278_ @ 0x80080278  (5 instructions)
 *
 *   80080278  38600000  li r3, 0
 *   8008027c  38000001  li r0, 1
 *   80080280  906dac10  stw r3, -0x53f0(r13)
 *   80080284  b00d8360  sth r0, -0x7ca0(r13)
 *   80080288  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li li stw sth blr
 *   exact_bytes      : false
 *   source sha256    : 914659c998a58f79ae37291595c0ec6da534e82c1b25e7fb8976e1b624c33c40
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x008 R_PPC_EMB_SDA21  DAT_804361b0             retail 0x804361b0  (sda, via registry+name)
 *   +0x00c R_PPC_EMB_SDA21  DAT_80433900             retail 0x80433900  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern short DAT_80433900;
extern int DAT_804361b0;

void f(void)
{
    DAT_804361b0 = 0;
    DAT_80433900 = 1;
}
