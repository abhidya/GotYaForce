#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8010858c(int param_1);
void FUN_80108604(int param_1);
void FUN_80108698(int param_1);
void FUN_801086d0(int param_1);
void FUN_80108770(int param_1);
void FUN_801087e8(int param_1);
void FUN_8010887c(int param_1);
void FUN_801088b4(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2940-2960 ==== */
// ==== 8010858c  FUN_8010858c ====

void FUN_8010858c(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcdae50,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2964-2987 ==== */
// ==== 80108604  FUN_80108604 ====

void FUN_80108604(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e4a18((double)FLOAT_80439500,param_1,(float *)&DAT_803251b0,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcdae50,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2991-2999 ==== */
// ==== 80108698  FUN_80108698 ====

void FUN_80108698(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 3003-3023 ==== */
// ==== 801086d0  FUN_801086d0 ====

void FUN_801086d0(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcdae50,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcdae50,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 3027-3047 ==== */
// ==== 80108770  FUN_80108770 ====

void FUN_80108770(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcdad60,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 3051-3074 ==== */
// ==== 801087e8  FUN_801087e8 ====

void FUN_801087e8(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e4a18((double)FLOAT_80439504,param_1,(float *)&DAT_803252a0,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcdad60,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 3078-3086 ==== */
// ==== 8010887c  FUN_8010887c ====

void FUN_8010887c(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 3090-3110 ==== */
// ==== 801088b4  FUN_801088b4 ====

void FUN_801088b4(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcdad60,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcdad60,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}
