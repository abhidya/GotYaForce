/* MATCHED  zz_008c098_ @ 0x8008c098  (7 instructions)
 *
 *   8008c098  38000000  li r0, 0
 *   8008c09c  900dac3c  stw r0, -0x53c4(r13)
 *   8008c0a0  900dac40  stw r0, -0x53c0(r13)
 *   8008c0a4  900dac34  stw r0, -0x53cc(r13)
 *   8008c0a8  900dac44  stw r0, -0x53bc(r13)
 *   8008c0ac  900dac30  stw r0, -0x53d0(r13)
 *   8008c0b0  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw stw stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 3cf1b89669f61d764bfb67ad80be0a6b3eeb8ae3644ef8d860601a20e217062a
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_804361dc             retail 0x804361dc  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_804361e0             retail 0x804361e0  (sda, via registry+name)
 *   +0x00c R_PPC_EMB_SDA21  DAT_804361d4             retail 0x804361d4  (sda, via registry+name)
 *   +0x010 R_PPC_EMB_SDA21  DAT_804361e4             retail 0x804361e4  (sda, via registry+name)
 *   +0x014 R_PPC_EMB_SDA21  DAT_804361d0             retail 0x804361d0  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804361d0;
extern int DAT_804361d4;
extern int DAT_804361dc;
extern int DAT_804361e0;
extern int DAT_804361e4;

void f(void)
{
    DAT_804361dc = 0;
    DAT_804361e0 = 0;
    DAT_804361d4 = 0;
    DAT_804361e4 = 0;
    DAT_804361d0 = 0;
}
