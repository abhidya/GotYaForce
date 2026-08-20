#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80014b08(int param_1);
void zz_0014b3c_(int param_1);
void zz_0014bc4_(int param_1);
void FUN_80014c20(int param_1);
void FUN_80014ce4(int param_1);
void zz_0014d38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, int param_11,short *param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0014f90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
int FUN_80015194(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, float *param_11,short *param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6321-6333 ==== */
// ==== 80014b08  FUN_80014b08 ====

void FUN_80014b08(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80436cac;
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  zz_0014b3c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6337-6361 ==== */
// ==== 80014b3c  zz_0014b3c_ ====

void zz_0014b3c_(int param_1)

{
  double dVar1;
  float fVar2;
  
  *(undefined1 *)(param_1 + 0x170) = 0;
  *(undefined1 *)(param_1 + 400) = 1;
  dVar1 = DOUBLE_80436bd0;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x18) == '\x01') {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar2 = FLOAT_80436cac;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(float *)(param_1 + 0x44) =
         -(fVar2 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000)
                          - dVar1));
    *(undefined2 *)(param_1 + 0x178) = 0;
    *(undefined1 *)(param_1 + 0x170) = 1;
    *(undefined1 *)(param_1 + 0x18c) = 0;
    *(undefined1 *)(param_1 + 0x18b) = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x3f0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6365-6388 ==== */
// ==== 80014bc4  zz_0014bc4_ ====

void zz_0014bc4_(int param_1)

{
  float fVar1;
  short sVar2;
  
  if (*(short *)(param_1 + 0x178) != 0) {
    *(short *)(param_1 + 0x178) = *(short *)(param_1 + 0x178) + -1;
    return;
  }
  *(undefined1 *)(param_1 + 0x170) = 1;
  *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + *(float *)(param_1 + 0x44);
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  fVar1 = FLOAT_80436bc4;
  if (0 < sVar2) {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6392-6432 ==== */
// ==== 80014c20  FUN_80014c20 ====

void FUN_80014c20(int param_1)

{
  bool bVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  bVar1 = false;
  iVar4 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar4 + 0x18) < '\x02') {
    if (*(char *)(iVar4 + 0x3f0) != *(char *)(param_1 + 0x18b)) {
      *(undefined1 *)(param_1 + 0x18c) = 1;
      bVar1 = true;
      *(undefined2 *)(param_1 + 0x178) = 0;
      *(undefined1 *)(param_1 + 0x18b) = *(undefined1 *)(iVar4 + 0x3f0);
    }
  }
  else {
    bVar1 = true;
    *(undefined1 *)(param_1 + 0x18c) = 0;
    if (*(char *)(iVar4 + 0x4a0) == '\0') {
      *(undefined2 *)(param_1 + 0x178) = 0x1e;
    }
    else {
      *(undefined2 *)(param_1 + 0x178) = 0;
    }
  }
  dVar2 = DOUBLE_80436bd0;
  if (bVar1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar3 = FLOAT_80436cac;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(float *)(param_1 + 0x44) =
         fVar3 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                        dVar2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6436-6449 ==== */
// ==== 80014ce4  FUN_80014ce4 ====

void FUN_80014ce4(int param_1)

{
  zz_0014bc4_(param_1);
  if (*(short *)(param_1 + 0x1e) < 1) {
    *(float *)(param_1 + 0x164) = FLOAT_80436cac;
    *(undefined1 *)(param_1 + 0x170) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 400) = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6453-6578 ==== */
// ==== 80014d38  zz_0014d38_ ====

void zz_0014d38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                int param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (*(short *)(param_11 + 2) == 0) {
    *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  }
  else {
    iVar1 = (int)*param_12;
    if (*(short *)(param_9 + 0x17a) != iVar1) {
      local_58 = DAT_802b0994;
      local_54 = DAT_802b0998;
      local_50 = DAT_802b099c;
      if (999 < iVar1) {
        iVar1 = 999;
      }
      *(short *)(param_9 + 0x17a) = (short)iVar1;
      iVar8 = 0;
      iVar7 = 0;
      uVar9 = 100;
      psVar3 = param_12;
      do {
        uVar4 = iVar1 / (int)uVar9;
        if (((uVar4 != 0) || (uVar9 == 1)) || (iVar7 != 0)) {
          if (iVar7 == 0) {
            *(short *)(param_9 + 0x17c) = 3 - (short)iVar8;
          }
          pfVar2 = (float *)0x13;
          iVar6 = param_9 + (2 - iVar8) * 4;
          iVar5 = *(int *)(iVar6 + 0xe0);
          uVar10 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x13,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_44 = uVar4 ^ 0x80000000;
          local_48 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_44) -
                                              DOUBLE_80436bd0),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          uVar10 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                               extraout_r4,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar5 = *(int *)(iVar6 + 0xec);
          pfVar2 = (float *)0x15;
          uVar10 = zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x15,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_3c = uVar4 ^ 0x80000000;
          local_40 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_3c) -
                                              DOUBLE_80436bd0),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5
                                ,extraout_r4_00,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar7 = iVar7 + 1;
          iVar1 = iVar1 - (iVar1 / (int)uVar9) * uVar9;
        }
        iVar8 = iVar8 + 1;
        uVar9 = uVar9 / 10;
      } while (iVar8 < 3);
      if (*(char *)(param_9 + 0x172) == '\0') {
        if (*(short *)(param_11 + 4) == 1) {
          if (*param_12 < param_12[1]) {
            *(undefined2 *)(param_9 + 0x17e) = 10;
          }
        }
        else if (*param_12 < *(short *)(param_11 + 2)) {
          *(undefined2 *)(param_9 + 0x17e) = 10;
        }
      }
      else {
        *(undefined2 *)(param_9 + 0x17e) = 0;
        *(undefined2 *)(param_9 + 0x182) = 0;
      }
      pfVar2 = (float *)0x43300000;
      uStack_3c = (int)*(short *)(param_9 + 0x17a) ^ 0x80000000;
      iVar1 = *(int *)(param_9 + 0x154);
      uStack_44 = (int)*(short *)(param_11 + 2) ^ 0x80000000;
      local_40 = 0x43300000;
      dVar12 = (double)FLOAT_80436bcc;
      local_48 = 0x43300000;
      dVar11 = DOUBLE_80436bd0;
      uVar10 = zz_00086b8_((double)(float)(dVar12 - (double)((float)((double)CONCAT44(0x43300000,
                                                                                      uStack_3c) -
                                                                    DOUBLE_80436bd0) /
                                                            (float)((double)CONCAT44(0x43300000,
                                                                                     uStack_44) -
                                                                   DOUBLE_80436bd0))),
                           DOUBLE_80436bd0,dVar12,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar1,0x43300000,psVar3,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,dVar12,param_4,param_5,param_6,param_7,param_8,iVar1,extraout_r4_01,
                  pfVar2,psVar3,param_13,param_14,param_15,param_16);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6582-6677 ==== */
// ==== 80014f90  zz_0014f90_ ====

void zz_0014f90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  float local_28;
  float local_24;
  float local_20;
  undefined4 auStack_1c [3];
  
  iVar5 = *(int *)(param_9 + 0x15c);
  iVar6 = *(char *)(param_9 + 399) * 4;
  iVar3 = param_10 + iVar6;
  pfVar2 = (float *)(*(int *)(param_10 + 0x4ac) + iVar6);
  uVar8 = zz_00086b8_((double)(*(float *)(iVar3 + 0x648) / pfVar2[0x61]),param_2,param_3,param_4,
                      param_5,param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,iVar3,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4,pfVar2
              ,iVar3,param_13,param_14,param_15,param_16);
  iVar6 = *(int *)(param_9 + 0x150);
  pfVar4 = (float *)0x0;
  if (*(int *)(iVar6 + 0x14) == 100) {
    dVar7 = (double)FLOAT_80436bc4;
    *(undefined1 *)(iVar6 + 0x10) = 0;
    dVar9 = (double)*(float *)(param_10 + *(char *)(param_9 + 399) * 4 + 0x648);
    if (dVar9 != dVar7) {
      pfVar4 = (float *)0x63;
    }
  }
  else {
    dVar9 = (double)FLOAT_80436bc4;
    if (dVar9 == (double)*(float *)(param_10 + *(char *)(param_9 + 399) * 4 + 0x648)) {
      pfVar4 = (float *)0x64;
    }
  }
  if (pfVar4 != (float *)0x0) {
    uVar8 = zz_0007908_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                        auStack_1c,pfVar2,iVar3,param_13,param_14,param_15,param_16);
    pfVar2 = pfVar4;
    uVar8 = zz_0006fb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                        iVar6,(int)pfVar4,iVar3,param_13,param_14,param_15,param_16);
    zz_0007834_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,auStack_1c,
                (char *)pfVar2,iVar3,param_13,param_14,param_15,param_16);
    if (pfVar4 == (float *)0x64) {
      *(undefined1 *)(iVar6 + 0x10) = 0;
    }
  }
  iVar5 = *(int *)(param_9 + 0x160);
  iVar6 = *(char *)(param_9 + 399) * 4;
  if (*(float *)(param_10 + iVar6 + 0x648) == *(float *)(*(int *)(param_10 + 0x4ac) + iVar6 + 0x184)
     ) {
    *(undefined1 *)(iVar5 + 0x10) = 1;
    if (*(char *)(param_9 + 0x18e) == '\0') {
      *(undefined2 *)(param_9 + 0x186) = 0;
      *(undefined2 *)(param_9 + 0x188) = 0;
    }
    else {
      *(short *)(param_9 + 0x186) = *(short *)(param_9 + 0x186) + 0x444;
      *(short *)(param_9 + 0x188) = *(short *)(param_9 + 0x188) + 1;
    }
    *(undefined1 *)(param_9 + 0x18e) = 1;
    fVar1 = FLOAT_80436cb0;
    if ((*(ushort *)(param_9 + 0x188) & 4) != 0) {
      fVar1 = FLOAT_80436bcc;
    }
    uVar8 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        DAT_804361fc,iVar5,pfVar2,iVar3,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4_00,
                pfVar2,iVar3,param_13,param_14,param_15,param_16);
    local_20 = FLOAT_80436bcc;
    dVar9 = zz_0045238_(*(short *)(param_9 + 0x186));
    local_28 = (float)((double)FLOAT_80436c44 * dVar9 + (double)FLOAT_80436cb4);
    local_24 = local_28;
    zz_0007ae4_(dVar9,(double)FLOAT_80436c44,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                &local_28,(char *)pfVar2,iVar3,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined1 *)(iVar5 + 0x10) = 0;
    *(undefined1 *)(param_9 + 0x18e) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 6681-6852 ==== */
// ==== 80015194  FUN_80015194 ====

/* WARNING: Removing unreachable block (ram,0x80015580) */
/* WARNING: Removing unreachable block (ram,0x800151a4) */

int FUN_80015194(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  short sVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  float *pfVar4;
  char *pcVar5;
  short *psVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 auStack_58 [2];
  float local_50;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  double local_38;
  
  sVar2 = *(short *)(param_11 + 1);
  iVar9 = 0;
  if (sVar2 == 1) {
    dVar11 = (double)*(float *)(param_12 + 2);
    if ((double)FLOAT_80436bc4 < dVar11) {
      iVar8 = *(int *)(param_9 + 0x154);
      pfVar4 = (float *)((int)*(short *)((int)param_11 + 2) * (int)*(short *)((int)param_11 + 6));
      local_48 = (double)(CONCAT44(0x43300000,pfVar4) ^ 0x80000000);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_80436bd0));
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,param_12,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_01
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar8 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_02
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      if (*param_12 == 0) {
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
        if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
          *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
        }
        iVar9 = 1;
      }
    }
  }
  else if (sVar2 < 1) {
    if (((-1 < sVar2) && (*param_12 == 0)) && (*(short *)(param_9 + 0x17e) == 0)) {
      iVar9 = *(int *)(param_9 + 0x154);
      local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)param_11 + 6)) ^ 0x80000000);
      dVar11 = (double)*(float *)(param_12 + 2);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_80436bd0));
      pfVar4 = param_11;
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4,
                  pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar9 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4_00
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  else if (sVar2 < 4) {
    pfVar4 = (float *)0x43300000;
    iVar8 = *(int *)(param_9 + 0x154);
    uStack_3c = (int)*(short *)((int)param_11 + 2) ^ 0x80000000;
    local_48 = (double)CONCAT44(0x43300000,(int)*param_12 ^ 0x80000000);
    param_3 = (double)FLOAT_80436bcc;
    local_40 = 0x43300000;
    dVar12 = (double)(float)(param_3 -
                            (double)((float)(local_48 - DOUBLE_80436bd0) /
                                    (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80436bd0
                                           )));
    psVar6 = param_12;
    dVar11 = DOUBLE_80436bd0;
    uVar10 = zz_00086b8_(dVar12,DOUBLE_80436bd0,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_804361fc,iVar8,0x43300000,param_12,param_13,param_14,param_15,param_16)
    ;
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_03,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    iVar8 = *(int *)(param_9 + 0x158);
    uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                         iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_04,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    if (*param_12 == 0) {
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  fVar3 = FLOAT_80436bc4;
  if (iVar9 != 0) {
    local_40 = 0x43300000;
    uStack_3c = (int)*(char *)(param_9 + 0x180) ^ 0x80000001;
    fVar3 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80436bd0);
  }
  dVar12 = (double)fVar3;
  uVar7 = 0;
  iVar8 = *(int *)(param_9 + 0x144);
  local_48 = (double)(longlong)(int)(DOUBLE_80436c00 * dVar12);
  uVar1 = (uint)(DOUBLE_80436c00 * DOUBLE_80436c08 * dVar12);
  local_38 = (double)(longlong)(int)uVar1;
  pcVar5 = (char *)(uVar1 & 0xff);
  dVar11 = DOUBLE_80436c00;
  zz_0007cd0_(iVar8,(int)(DOUBLE_80436c00 * dVar12) & 0xff,pcVar5,0);
  dVar12 = (double)zz_0007cac_((double)(float)((double)FLOAT_80436cbc * dVar12 +
                                              (double)FLOAT_80436cb8),iVar8);
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  if (*(char *)(param_9 + 0x180) == '\0') {
    *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 1;
  }
  else {
    *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 1;
  }
  if (*(short *)(param_9 + 0x17e) == 0) {
    dVar12 = (double)*(float *)(param_12 + 2);
    if (dVar12 <= (double)FLOAT_80436bc4) {
      if (*(short *)(param_9 + 0x182) != 0) {
        *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
      }
    }
    else if ((*(short *)(param_11 + 1) != 2) && (*(short *)(param_11 + 1) != 3)) {
      *(undefined2 *)(param_9 + 0x184) = 0xf000;
      *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
    }
  }
  else {
    *(short *)(param_9 + 0x17e) = *(short *)(param_9 + 0x17e) + -1;
    *(undefined2 *)(param_9 + 0x184) = 0x1000;
    *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
  }
  zz_0007a60_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16)
  ;
  local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x182)) ^ 0x80000000);
  local_50 = (float)((double)FLOAT_80436c30 * (double)(float)(local_38 - DOUBLE_80436bd0));
  zz_0007988_(DOUBLE_80436bd0,(double)FLOAT_80436c30,param_3,param_4,param_5,param_6,param_7,param_8
              ,*(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16
             );
  return iVar9;
}
