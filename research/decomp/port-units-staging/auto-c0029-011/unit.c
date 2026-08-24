#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801072b4(int param_1);
void FUN_801072fc(int param_1);
void FUN_80107320(int param_1);
void FUN_80107344(int param_1);
void FUN_80107368(int param_1);
void FUN_8010738c(int param_1);
void FUN_801073b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
bool zz_01073f8_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2177-2185 ==== */
// ==== 801072b4  FUN_801072b4 ====

void FUN_801072b4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80322e98)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2189-2196 ==== */
// ==== 801072fc  FUN_801072fc ====

void FUN_801072fc(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2200-2207 ==== */
// ==== 80107320  FUN_80107320 ====

void FUN_80107320(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2211-2218 ==== */
// ==== 80107344  FUN_80107344 ====

void FUN_80107344(int param_1)

{
  zz_010bd10_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2222-2229 ==== */
// ==== 80107368  FUN_80107368 ====

void FUN_80107368(int param_1)

{
  zz_010c220_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2233-2240 ==== */
// ==== 8010738c  FUN_8010738c ====

void FUN_8010738c(int param_1)

{
  zz_010c590_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2244-2260 ==== */
// ==== 801073b0  FUN_801073b0 ====

void FUN_801073b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  
  zz_006a474_(param_9);
  dVar1 = (double)FLOAT_804394b0;
  *(float *)(param_9 + 0x694) = (float)(dVar1 + (double)*(float *)(param_9 + 0x1dc8));
  zz_006a668_(dVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,5,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2264-2302 ==== */
// ==== 801073f8  zz_01073f8_ ====

bool zz_01073f8_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined2 *)(param_1 + 0x784) = *(undefined2 *)(param_1 + 0x79e);
    *(undefined2 *)(param_1 + 0x786) = *(undefined2 *)(param_1 + 0x79e);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x22;
    *(code **)(puVar1 + 0xc) = FUN_80107510;
    *(code **)(puVar1 + 0x10c) = FUN_80107e1c;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return puVar1 != (undefined1 *)0x0;
}
