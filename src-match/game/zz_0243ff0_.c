/* MATCHED  zz_0243ff0_ @ 0x80243ff0  (3 instructions)
 *
 *   80243ff0  38000000  li r0, 0
 *   80243ff4  900db388  stw r0, -0x4c78(r13)
 *   80243ff8  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : c37ca624ef97c076a7f000ea2382188a3abdc7f4107ca53cd783b2fb55c4ac5d
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_80436928             retail 0x80436928  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_80436928;

void f(void)
{
    DAT_80436928 = 0;
}
