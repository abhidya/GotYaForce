#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80108014(int param_1);
void FUN_80108034(int param_1);
void FUN_80108078(undefined4 param_1,char param_2,char param_3);
void FUN_801080e4(int param_1);
void FUN_80108120(int param_1);
void FUN_80108168(int param_1);
void FUN_8010818c(int param_1);
void FUN_801081b0(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2679-2686 ==== */
// ==== 80108014  FUN_80108014 ====

void FUN_80108014(int param_1)

{
  zz_010a4ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2690-2699 ==== */
// ==== 80108034  FUN_80108034 ====

void FUN_80108034(int param_1)

{
  if (*(char *)(param_1 + 0x146) != '\0') {
    zz_00f0104_(param_1,10,3);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2703-2710 ==== */
// ==== 80108078  FUN_80108078 ====

void FUN_80108078(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_804344d0)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2714-2721 ==== */
// ==== 801080e4  FUN_801080e4 ====

void FUN_801080e4(int param_1)

{
  (*(code *)(&PTR_FUN_803240f8)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2725-2733 ==== */
// ==== 80108120  FUN_80108120 ====

void FUN_80108120(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80324108)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2737-2744 ==== */
// ==== 80108168  FUN_80108168 ====

void FUN_80108168(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2748-2755 ==== */
// ==== 8010818c  FUN_8010818c ====

void FUN_8010818c(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2759-2766 ==== */
// ==== 801081b0  FUN_801081b0 ====

void FUN_801081b0(int param_1)

{
  zz_010bd10_(param_1);
  return;
}
