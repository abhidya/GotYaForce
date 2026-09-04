/* MATCHED  zz_0027c1c_ @ 0x80027c1c  (6 instructions)
 *
 *   80027c1c  806dab6c  lwz r3, -0x5494(r13)
 *   80027c20  38000000  li r0, 0
 *   80027c24  98030008  stb r0, 8(r3)
 *   80027c28  806dab6c  lwz r3, -0x5494(r13)
 *   80027c2c  b0030004  sth r0, 4(r3)
 *   80027c30  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li stb lwz sth blr
 *   exact_bytes      : false
 *   source sha256    : d1c3788b4d59cd2173cf14e32a7304a13c10c7e67ce1f08f5134473b6b25d7dd
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  DAT_8043610c             retail 0x8043610c  (sda, via registry+name)
 *   +0x00c R_PPC_EMB_SDA21  DAT_8043610c             retail 0x8043610c  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G8043610c {
    char pad_0[0x4];
    short          field_4;
    char pad_6[0x2];
    char           field_8;
} G8043610c;

extern G8043610c *DAT_8043610c;

void f(void)
{
    DAT_8043610c->field_8 = 0;
    DAT_8043610c->field_4 = 0;
}
