/* MATCHED  zz_000a134_ @ 0x8000a134  (4 instructions)
 *
 *   8000a134  806dab30  lwz r3, -0x54d0(r13)
 *   8000a138  38000000  li r0, 0
 *   8000a13c  98030003  stb r0, 3(r3)
 *   8000a140  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li stb blr
 *   exact_bytes      : false
 *   source sha256    : 9f319cf794c2a65f3c56e9d0fdb58d43b85be4c3cfdf8cfcb94994e9f82b71ef
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_804360d0             retail 0x804360d0  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G804360d0 {
    char pad_0[0x3];
    char           field_3;
} G804360d0;

extern G804360d0 *DAT_804360d0;

void f(void)
{
    DAT_804360d0->field_3 = 0;
}
