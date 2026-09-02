#include "gf_indirect_lowering.h"
#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80079978(int param_1);
void FUN_800799ac(int param_1);
void FUN_800799cc(int param_1);
void FUN_800799ec(int param_1,char param_2);
void FUN_80079a40(int param_1);
void FUN_80079a7c(int param_1);
void FUN_80079ab8(int param_1);
void FUN_80079b08(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1569-1576 ==== */
// ==== 80079978  FUN_80079978 ====

void FUN_80079978(int param_1)

{
  zz_00795e0_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1580-1587 ==== */
// ==== 800799ac  FUN_800799ac ====

void FUN_800799ac(int param_1)

{
  zz_0079754_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1591-1598 ==== */
// ==== 800799cc  FUN_800799cc ====

void FUN_800799cc(int param_1)

{
  zz_007978c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1602-1615 ==== */
// ==== 800799ec  FUN_800799ec ====

void FUN_800799ec(int param_1,char param_2)

{
  if (param_2 == '\x01') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((param_2 < '\x01') && (-1 < param_2)) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    zz_001ab6c_(param_1,0x47);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1619-1626 ==== */
// ==== 80079a40  FUN_80079a40 ====

void FUN_80079a40(int param_1)

{
  do { __gf_indirect_call __gf_c; __gf_indirect_begin(&__gf_c); __gf_c.frame.arg_count = 0u; __gf_dispatch_at(0x00079a40u, (unsigned int)((&PTR_FUN_802d65b0)[*(char *)(param_1 + 0x580)]), __GF_ADDR(&__gf_c.frame), __GF_ADDR(__gf_c.classes)); } while (0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1630-1637 ==== */
// ==== 80079a7c  FUN_80079a7c ====

void FUN_80079a7c(int param_1)

{
  do { __gf_indirect_call __gf_c; __gf_indirect_begin(&__gf_c); __gf_c.frame.arg_count = 0u; __gf_dispatch_at(0x00079a7cu, (unsigned int)((&PTR_FUN_802d65bc)[*(char *)(param_1 + 0x581)]), __GF_ADDR(&__gf_c.frame), __GF_ADDR(__gf_c.classes)); } while (0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1641-1649 ==== */
// ==== 80079ab8  FUN_80079ab8 ====

void FUN_80079ab8(int param_1)

{
  do { __gf_indirect_call __gf_c; __gf_indirect_begin(&__gf_c); __gf_c.frame.arg_count = 0u; __gf_dispatch_at(0x00079ab8u, (unsigned int)((&PTR_FUN_802d65d0)[*(char *)(param_1 + 0x541)]), __GF_ADDR(&__gf_c.frame), __GF_ADDR(__gf_c.classes)); } while (0);
  zz_0079d54_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1653-1674 ==== */
// ==== 80079b08  FUN_80079b08 ====

void FUN_80079b08(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(char *)(param_1 + 0x581) == '\x03') {
    *(float *)(param_1 + 0x80c) = FLOAT_804378e8;
  }
  *(float *)(param_1 + 0x558) = FLOAT_804378ec;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  fVar1 = FLOAT_804378e8;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  return;
}
