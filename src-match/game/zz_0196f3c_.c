/* MATCHED  zz_0196f3c_ @ 0x80196f3c  (10 instructions)
 *
 *   80196f3c  806d8394  lwz r3, -0x7c6c(r13)
 *   80196f40  38000000  li r0, 0
 *   80196f44  b003182a  sth r0, 0x182a(r3)
 *   80196f48  806d8394  lwz r3, -0x7c6c(r13)
 *   80196f4c  b003182c  sth r0, 0x182c(r3)
 *   80196f50  806d8394  lwz r3, -0x7c6c(r13)
 *   80196f54  b003182e  sth r0, 0x182e(r3)
 *   80196f58  806d8394  lwz r3, -0x7c6c(r13)
 *   80196f5c  b0031830  sth r0, 0x1830(r3)
 *   80196f60  4e800020  blr
 *
 * PROVENANCE -- produced by research/tools/matching-decomp/sda_recover.py,
 * recorded through loop.py's record_match.
 *   candidate source : sda-leaf (small-data globals, data relocations address-checked by datareloc.py)
 *   iterations       : 1
 *   model calls      : 0
 *   permuter steps   : 0
 *   shape            : lwz li sth lwz sth lwz sth lwz sth blr
 *   exact_bytes      : false
 *   source sha256    : 81c0f581d0872d558f6164083930ae5415348a211131b5345052ca7348f35174
 *
 * DATA-RELOCATION VERIFICATION (datareloc.py) -- every data relocation below was
 * checked against the address the RETAIL encoding names, not merely masked:
 *   +0x000 R_PPC_EMB_SDA21  PTR_DAT_80433934         retail 0x80433934  (sda, via registry+name)
 *   +0x00c R_PPC_EMB_SDA21  PTR_DAT_80433934         retail 0x80433934  (sda, via registry+name)
 *   +0x014 R_PPC_EMB_SDA21  PTR_DAT_80433934         retail 0x80433934  (sda, via registry+name)
 *   +0x01c R_PPC_EMB_SDA21  PTR_DAT_80433934         retail 0x80433934  (sda, via registry+name)
 * _SDA_BASE_ (r13) = 0x8043b5a0, _SDA2_BASE_ (r2) = 0x8043ea20, derived from
 * __init_registers and cross-checked against the DOL section table.
 * Re-proved by src-match/verify.py against the retail DOL; the hash
 * above covers the C below this header only.
 */
typedef struct G80433934 {
    char pad_0[0x182a];
    short          field_182a;
    short          field_182c;
    short          field_182e;
    short          field_1830;
} G80433934;

extern G80433934 *PTR_DAT_80433934;

void f(void)
{
    PTR_DAT_80433934->field_182a = 0;
    PTR_DAT_80433934->field_182c = 0;
    PTR_DAT_80433934->field_182e = 0;
    PTR_DAT_80433934->field_1830 = 0;
}
