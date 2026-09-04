/* MATCHED  zz_000a144_ @ 0x8000a144  (4 instructions)
 *
 *   8000a144  38000000  li r0, 0
 *   8000a148  900dab2c  stw r0, -0x54d4(r13)
 *   8000a14c  900dab28  stw r0, -0x54d8(r13)
 *   8000a150  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw stw blr
 *   exact_bytes      : false
 *   source sha256    : 2448eddeb31fc94f06b6685044915114fcff5e2ede1d85780ecd1eaeddfbf3b6
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_804360cc             retail 0x804360cc  (sda, via registry+name)
 *   +0x008 R_PPC_EMB_SDA21  DAT_804360c8             retail 0x804360c8  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804360c8;
extern int DAT_804360cc;

void f(void)
{
    DAT_804360cc = 0;
    DAT_804360c8 = 0;
}
