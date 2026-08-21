#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_00b9e60_(int param_1,short *param_2);
void FUN_800ba240(int param_1);
void FUN_800ba2c4(int param_1);
void FUN_800ba324(undefined4 param_1,char param_2,char param_3);
void FUN_800ba364(int param_1,int param_2);
void FUN_800ba390(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0018.c 4499-4618 ==== */
// ==== 800b9e60  zz_00b9e60_ ====

void zz_00b9e60_(int param_1,short *param_2)

{
  short *psVar1;
  float fVar2;
  undefined4 uVar3;
  short sVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  short *psVar10;
  short *psVar11;
  short *psVar12;
  
  cVar6 = *(char *)(param_1 + 0x6e9);
  if (cVar6 == '\0') {
    cVar6 = *(char *)(param_2 + 0x16);
  }
  if ((int)cVar6 == (int)*(char *)(param_2 + 0x16)) {
    psVar11 = param_2 + 6;
    psVar12 = param_2 + 0xc;
    iVar7 = 2;
    psVar10 = param_2;
    do {
      sVar4 = *psVar12;
      sVar9 = *psVar11 - *psVar10;
      if ((int)sVar4 < (int)(short)(*psVar11 - *psVar10)) {
        sVar9 = sVar4;
      }
      iVar8 = -(int)sVar4;
      if (sVar9 < iVar8) {
        sVar9 = (short)iVar8;
      }
      *psVar10 = *psVar10 + sVar9;
      sVar4 = psVar12[1];
      sVar9 = psVar11[1] - psVar10[1];
      if ((int)sVar4 < (int)(short)(psVar11[1] - psVar10[1])) {
        sVar9 = sVar4;
      }
      iVar8 = -(int)sVar4;
      if (sVar9 < iVar8) {
        sVar9 = (short)iVar8;
      }
      psVar10[1] = psVar10[1] + sVar9;
      psVar1 = psVar11 + 2;
      psVar11 = psVar11 + 3;
      sVar4 = psVar12[2];
      psVar12 = psVar12 + 3;
      sVar9 = *psVar1 - psVar10[2];
      if ((int)sVar4 < (int)(short)(*psVar1 - psVar10[2])) {
        sVar9 = sVar4;
      }
      iVar8 = -(int)sVar4;
      if (sVar9 < iVar8) {
        sVar9 = (short)iVar8;
      }
      psVar10[2] = psVar10[2] + sVar9;
      psVar10 = psVar10 + 3;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  else {
    iVar7 = (cVar6 + -1) * 0x18;
    *(undefined4 *)(param_2 + 6) = *(undefined4 *)(&DAT_803002d8 + iVar7);
    param_2[8] = *(short *)(&DAT_803002dc + iVar7);
    *(undefined4 *)(param_2 + 9) = *(undefined4 *)(&DAT_803002de + iVar7);
    param_2[0xb] = *(short *)(&DAT_803002e2 + iVar7);
    *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(&DAT_803002e4 + iVar7);
    param_2[0xe] = *(short *)(&DAT_803002e8 + iVar7);
    *(undefined4 *)(param_2 + 0xf) = *(undefined4 *)(&DAT_803002ea + iVar7);
    param_2[0x11] = *(short *)(&DAT_803002ee + iVar7);
  }
  iVar7 = (cVar6 + -1) * 0x10;
  fVar2 = *(float *)(&DAT_80300324 + iVar7);
  fVar5 = *(float *)(&DAT_80300320 + iVar7) - *(float *)(param_2 + 0x12);
  if (fVar2 < *(float *)(&DAT_80300320 + iVar7) - *(float *)(param_2 + 0x12)) {
    fVar5 = fVar2;
  }
  if (fVar5 < -fVar2) {
    fVar5 = -fVar2;
  }
  *(float *)(param_2 + 0x12) = *(float *)(param_2 + 0x12) + fVar5;
  fVar2 = *(float *)(&DAT_8030032c + iVar7);
  fVar5 = *(float *)(&DAT_80300328 + iVar7) - *(float *)(param_2 + 0x14);
  if (fVar2 < *(float *)(&DAT_80300328 + iVar7) - *(float *)(param_2 + 0x14)) {
    fVar5 = fVar2;
  }
  if (fVar5 < -fVar2) {
    fVar5 = -fVar2;
  }
  *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar5;
  *(char *)(param_2 + 0x16) = cVar6;
  *(undefined4 *)(param_1 + 0x194c) = *(undefined4 *)param_2;
  *(short *)(param_1 + 0x1950) = param_2[2];
  *(short *)(param_1 + 0x1952) = *param_2;
  *(short *)(param_1 + 0x1954) = -param_2[1];
  *(short *)(param_1 + 0x1956) = -param_2[2];
  if (*(char *)(param_2 + 0x16) == '\x02') {
    *(undefined2 *)(param_1 + 0x194e) =
         *(undefined2 *)(&DAT_80433ad0 + (*(uint *)(PTR_DAT_80433934 + 0xb0) & 3) * 2);
    *(short *)(param_1 + 0x1954) = -*(short *)(param_1 + 0x194e);
    zz_00f0104_(param_1,0x11,6);
  }
  uVar3 = *(undefined4 *)(param_2 + 0x12);
  *(undefined4 *)(param_1 + 0x16d0) = uVar3;
  *(undefined4 *)(param_1 + 0x16c4) = uVar3;
  uVar3 = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(param_1 + 0x16d4) = uVar3;
  *(undefined4 *)(param_1 + 0x16c8) = uVar3;
  *(undefined4 *)(param_1 + 0x1958) = *(undefined4 *)(param_2 + 3);
  *(short *)(param_1 + 0x195c) = param_2[5];
  *(short *)(param_1 + 0x195e) = param_2[3];
  *(short *)(param_1 + 0x1960) = -param_2[4];
  *(short *)(param_1 + 0x1962) = -param_2[5];
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0018.c 4622-4631 ==== */
// ==== 800ba240  FUN_800ba240 ====

void FUN_800ba240(int param_1)

{
  zz_00cbe9c_(param_1);
  zz_00b9e30_(param_1,(short *)(param_1 + 0x144));
  *(undefined1 *)(param_1 + 0x172) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0018.c 4635-4645 ==== */
// ==== 800ba2c4  FUN_800ba2c4 ====

void FUN_800ba2c4(int param_1)

{
  zz_00b9e60_(param_1,(short *)(param_1 + 0x144));
  if ((*(char *)(param_1 + 0x493) != '\0') && (FLOAT_804384e8 < *(float *)(param_1 + 0x12e4))) {
    *(float *)(param_1 + 0x12e4) = FLOAT_804384e8;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0018.c 4649-4656 ==== */
// ==== 800ba324  FUN_800ba324 ====

void FUN_800ba324(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80300390)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0018.c 4660-4667 ==== */
// ==== 800ba364  FUN_800ba364 ====

void FUN_800ba364(int param_1,int param_2)

{
  zz_0099e70_(param_1,(&DAT_80433ad8)[param_2]);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0018.c 4671-4678 ==== */
// ==== 800ba390  FUN_800ba390 ====

void FUN_800ba390(int param_1)

{
  zz_0137540_(param_1,0);
  return;
}
