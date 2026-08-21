#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801b7bf0(void);
void zz_01b7c54_(uint param_1,uint param_2,short param_3,short param_4,short param_5,short param_6);
void FUN_801b7d70(int param_1);
void FUN_801b7ea8(int param_1);
void FUN_801b7ef0(undefined4 param_1,char param_2,char param_3);
void FUN_801b7f30(int param_1,int param_2);
void FUN_801b7f8c(int param_1);
void FUN_801b7fc0(int param_1,uint param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2259-2272 ==== */
// ==== 801b7bf0  FUN_801b7bf0 ====

void FUN_801b7bf0(void)

{
  int iVar1;
  char cVar2;
  
  iVar1 = DAT_803d4a58;
  if ((DAT_803d4a50 != '\0') && (cVar2 = zz_01b7968_(0), cVar2 != '\0')) {
    zz_01b7c54_((uint)*(ushort *)(iVar1 + 0x14),(uint)*(ushort *)(iVar1 + 0x16),0,0,0x280,0x1c0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2276-2283 ==== */
// ==== 801b7c54  zz_01b7c54_ ====

void zz_01b7c54_(uint param_1,uint param_2,short param_3,short param_4,short param_5,short param_6)

{
  FUN_8002b7ac(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2287-2308 ==== */
// ==== 801b7d70  FUN_801b7d70 ====

void FUN_801b7d70(int param_1)

{
  *(undefined1 *)(param_1 + 0x582) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  zz_00e7758_(param_1,1,0);
  zz_00e7758_(param_1,1,1);
  *(float *)(param_1 + 0x144) = FLOAT_8043ba18;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x14a) = 0;
  *(undefined1 *)(param_1 + 0x14b) = 0;
  if (*(char *)(param_1 + 0x3ec) == '\x04') {
    *(float *)(param_1 + 0x154) = FLOAT_8043ba1c;
  }
  else {
    *(float *)(param_1 + 0x154) = FLOAT_8043ba20;
  }
  *(float *)(param_1 + 0x150) = FLOAT_8043ba24;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2312-2319 ==== */
// ==== 801b7ea8  FUN_801b7ea8 ====

void FUN_801b7ea8(int param_1)

{
  zz_0156a58_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2323-2330 ==== */
// ==== 801b7ef0  FUN_801b7ef0 ====

void FUN_801b7ef0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803821b8)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2334-2344 ==== */
// ==== 801b7f30  FUN_801b7f30 ====

void FUN_801b7f30(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x582) == '\0') {
    zz_006bda8_(param_1);
    zz_0099e70_(param_1,(&DAT_803821d4)[param_2]);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2348-2355 ==== */
// ==== 801b7f8c  FUN_801b7f8c ====

void FUN_801b7f8c(int param_1)

{
  zz_0137540_(param_1,*(char *)(param_1 + 0x582) == '\x01');
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2359-2375 ==== */
// ==== 801b7fc0  FUN_801b7fc0 ====

void FUN_801b7fc0(int param_1,uint param_2)

{
  if ((*(char *)(param_1 + 0x582) == '\x01') && (param_2 != 3)) {
    param_2 = param_2 ^ 3;
  }
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if ((param_2 & 1) != 0) {
    zz_001ab6c_(param_1,0x58);
  }
  if ((param_2 & 2) != 0) {
    zz_001ab6c_(param_1,0x57);
  }
  return;
}
