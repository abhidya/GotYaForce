#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
int zz_0151668_(int param_1);
void zz_015188c_(int param_1);
void zz_0151960_(int param_1);
void zz_0151ab8_(int param_1);
void zz_0151af0_(int param_1);
void FUN_80151c38(int param_1);
void FUN_80151c74(int param_1);
void FUN_80151ca0(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2746-2793 ==== */
// ==== 80151668  zz_0151668_ ====

int zz_0151668_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  
  iVar5 = 0;
  iVar4 = param_1 + 0x144;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar2) != 0) {
      iVar1 = *(int *)(param_1 + 0x54) + iVar5;
      if (*(short *)(iVar1 + 0x20) == 0) {
        dVar7 = (double)FLOAT_8043a4fc;
        *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) - *(float *)(iVar4 + 0xc);
        dVar6 = (double)*(float *)(param_1 + 0x14c);
        if ((dVar6 <= dVar7) && (dVar7 = dVar6, dVar6 < (double)FLOAT_8043a4f8)) {
          dVar7 = (double)FLOAT_8043a4f8;
        }
      }
      else {
        dVar7 = (double)FLOAT_8043a4fc;
        *(float *)(iVar1 + 0x1c) = *(float *)(iVar1 + 0x1c) - *(float *)(iVar4 + 0xc);
        dVar6 = (double)*(float *)(iVar1 + 0x1c);
        if ((dVar6 <= dVar7) && (dVar7 = dVar6, dVar6 < (double)FLOAT_8043a4f8)) {
          dVar7 = (double)FLOAT_8043a4f8;
        }
      }
      if (dVar7 <= (double)FLOAT_8043a4f8) {
        *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar2);
      }
      else {
        zz_0007cac_(dVar7,*(int *)(iVar3 + 0xe0));
      }
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 4;
  }
  return (int)*(short *)(param_1 + 0x1e);
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2797-2820 ==== */
// ==== 8015188c  zz_015188c_ ====

void zz_015188c_(int param_1)

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
    FUN_800e4294(param_1,-0x7fcbe318,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fcbe2b8,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fcbe258,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fcbe1f8,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2824-2856 ==== */
// ==== 80151960  zz_0151960_ ====

void zz_0151960_(int param_1)

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
      FUN_800e43e0(param_1,(float *)&DAT_80341ce8,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80341d48,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80341da8,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80341e08,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)0x0);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcbe318,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fcbe2b8,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fcbe258,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fcbe1f8,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2860-2868 ==== */
// ==== 80151ab8  zz_0151ab8_ ====

void zz_0151ab8_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2872-2898 ==== */
// ==== 80151af0  zz_0151af0_ ====

void zz_0151af0_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe318,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe2b8,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe258,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe1f8,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fcbe318,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fcbe2b8,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fcbe258,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcbe1f8,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2902-2909 ==== */
// ==== 80151c38  FUN_80151c38 ====

void FUN_80151c38(int param_1)

{
  zz_015188c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2913-2920 ==== */
// ==== 80151c74  FUN_80151c74 ====

void FUN_80151c74(int param_1)

{
  zz_0151960_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 2924-2931 ==== */
// ==== 80151ca0  FUN_80151ca0 ====

void FUN_80151ca0(int param_1)

{
  zz_0151ab8_(param_1);
  return;
}
