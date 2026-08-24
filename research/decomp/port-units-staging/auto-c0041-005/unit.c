#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8015d62c(int param_1);
void FUN_8015d650(int param_1);
void zz_015d770_(int param_1);
void zz_015d844_(int param_1);
void zz_015d99c_(int param_1);
void zz_015d9d4_(int param_1);
void FUN_8015db1c(int param_1);
void FUN_8015dba4(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 978-985 ==== */
// ==== 8015d62c  FUN_8015d62c ====

void FUN_8015d62c(int param_1)

{
  zz_014ad94_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 989-996 ==== */
// ==== 8015d650  FUN_8015d650 ====

void FUN_8015d650(int param_1)

{
  zz_014b22c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 1000-1023 ==== */
// ==== 8015d770  zz_015d770_ ====

void zz_015d770_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(300);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    FUN_800e4294(param_1,-0x7fcb7608,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fcb75a8,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fcb7548,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fcb74e8,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 1027-1059 ==== */
// ==== 8015d844  zz_015d844_ ====

void zz_015d844_(int param_1)

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
      FUN_800e43e0(param_1,(float *)&DAT_803489f8,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80348a58,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80348ab8,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80348b18,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)0x0);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcb7608,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fcb75a8,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fcb7548,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fcb74e8,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 1063-1071 ==== */
// ==== 8015d99c  zz_015d99c_ ====

void zz_015d99c_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 1075-1101 ==== */
// ==== 8015d9d4  zz_015d9d4_ ====

void zz_015d9d4_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb7608,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb75a8,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb7548,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb74e8,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fcb7608,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fcb75a8,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fcb7548,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcb74e8,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 1105-1121 ==== */
// ==== 8015db1c  FUN_8015db1c ====

void FUN_8015db1c(int param_1)

{
  short sVar1;
  
  zz_015d770_(param_1);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x909) {
    zz_0162f78_(param_1,2);
  }
  else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
    zz_0162f78_(param_1,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0041.c 1125-1132 ==== */
// ==== 8015dba4  FUN_8015dba4 ====

void FUN_8015dba4(int param_1)

{
  zz_015d844_(param_1);
  return;
}
