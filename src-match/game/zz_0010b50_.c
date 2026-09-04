/* MATCHED  zz_0010b50_ @ 0x80010b50  (5 instructions)
 *
 *   80010b50  38000000  li r0, 0
 *   80010b54  980dab3c  stb r0, -0x54c4(r13)
 *   80010b58  980dab3a  stb r0, -0x54c6(r13)
 *   80010b5c  b00dab38  sth r0, -0x54c8(r13)
 *   80010b60  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stb stb sth blr
 *   exact_bytes      : false
 *   source sha256    : 58e264e81609bbf28106775363a18413800d01c93ada7dabb0c52b37c4c2bd24
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_804360dc             retail 0x804360dc  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_804360da             retail 0x804360da  (sda, via registry+name)
 *   +0x00c R_PPC_EMB_SDA21  DAT_804360d8             retail 0x804360d8  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern short DAT_804360d8;
extern char DAT_804360da;
extern char DAT_804360dc;

void f(void)
{
    DAT_804360dc = 0;
    DAT_804360da = 0;
    DAT_804360d8 = 0;
}
