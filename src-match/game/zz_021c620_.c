/* MATCHED  zz_021c620_ @ 0x8021c620  (3 instructions)
 *
 *   8021c620  38000000  li r0, 0
 *   8021c624  900db210  stw r0, -0x4df0(r13)
 *   8021c628  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : li stw blr
 *   exact_bytes      : false
 *   source sha256    : 2cf45d221577e238bddd4de37fa2e3531127322beeaf38a1281a35ec4e7a5b6a
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x004 R_PPC_EMB_SDA21  DAT_804367b0             retail 0x804367b0  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
extern int DAT_804367b0;

void f(void)
{
    DAT_804367b0 = 0;
}
