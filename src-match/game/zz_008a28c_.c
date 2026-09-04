/* MATCHED  zz_008a28c_ @ 0x8008a28c  (12 instructions)
 *
 *   8008a28c  38000000  li r0, 0
 *   8008a290  b00dacb0  sth r0, -0x5350(r13)
 *   8008a294  b00dacae  sth r0, -0x5352(r13)
 *   8008a298  b00dacac  sth r0, -0x5354(r13)
 *   8008a29c  b00dacaa  sth r0, -0x5356(r13)
 *   8008a2a0  b00daca8  sth r0, -0x5358(r13)
 *   8008a2a4  b00daca6  sth r0, -0x535a(r13)
 *   8008a2a8  b00daca4  sth r0, -0x535c(r13)
 *   8008a2ac  b00daca2  sth r0, -0x535e(r13)
 *   8008a2b0  b00daca0  sth r0, -0x5360(r13)
 *   8008a2b4  b00dac9e  sth r0, -0x5362(r13)
 *   8008a2b8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li sth sth sth sth sth sth sth sth sth sth blr
 *   exact_bytes      : false
 *   source sha256    : 9cacd37d60a5ca7ce1ab19905da832884b0b81fb6f547be457a6b8b8ac633cab
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_80436250             retail 0x80436250  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_8043624e             retail 0x8043624e  (sda, via registry+name)
 *   +0x00c R_PPC_EMB_SDA21  DAT_8043624c             retail 0x8043624c  (sda, via registry+name)
 *   +0x010 R_PPC_EMB_SDA21  DAT_8043624a             retail 0x8043624a  (sda, via registry+name)
 *   +0x014 R_PPC_EMB_SDA21  DAT_80436248             retail 0x80436248  (sda, via registry+name)
 *   +0x018 R_PPC_EMB_SDA21  DAT_80436246             retail 0x80436246  (sda, via registry+name)
 *   +0x01c R_PPC_EMB_SDA21  DAT_80436244             retail 0x80436244  (sda, via registry+name)
 *   +0x020 R_PPC_EMB_SDA21  DAT_80436242             retail 0x80436242  (sda, via registry+name)
 *   +0x024 R_PPC_EMB_SDA21  DAT_80436240             retail 0x80436240  (sda, via registry+name)
 *   +0x028 R_PPC_EMB_SDA21  DAT_8043623e             retail 0x8043623e  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern short DAT_8043623e;
extern short DAT_80436240;
extern short DAT_80436242;
extern short DAT_80436244;
extern short DAT_80436246;
extern short DAT_80436248;
extern short DAT_8043624a;
extern short DAT_8043624c;
extern short DAT_8043624e;
extern short DAT_80436250;

void f(void)
{
    DAT_80436250 = 0;
    DAT_8043624e = 0;
    DAT_8043624c = 0;
    DAT_8043624a = 0;
    DAT_80436248 = 0;
    DAT_80436246 = 0;
    DAT_80436244 = 0;
    DAT_80436242 = 0;
    DAT_80436240 = 0;
    DAT_8043623e = 0;
}
