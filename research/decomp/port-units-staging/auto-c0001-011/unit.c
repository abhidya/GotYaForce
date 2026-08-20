#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0012638_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_0012984_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, float *param_11,undefined *param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0012d08_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0012e4c_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
void FUN_80012e74(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5, undefined4 param_6,undefined4 param_7,undefined4 param_8);
void zz_00131b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0013304_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_00133f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4679-4820 ==== */
// ==== 80012638  zz_0012638_ ====

void zz_0012638_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  bool bVar2;
  undefined *puVar3;
  float fVar4;
  short sVar6;
  int iVar5;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 extraout_r4;
  uint uVar10;
  float *pfVar11;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  
  if (*(char *)(param_9 + 0x176) != '\x02') {
    cVar1 = *(char *)(param_9 + 0x19);
    if (((cVar1 != '\x01') && (cVar1 < '\x01')) && (-1 < cVar1)) {
      sVar6 = *(short *)(param_9 + 0x1c) + -1;
      *(short *)(param_9 + 0x1c) = sVar6;
      fVar4 = FLOAT_80436bc4;
      if (sVar6 < 1) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0x164) = fVar4;
      }
      else {
        *(float *)(param_9 + 0x164) = *(float *)(param_9 + 0x164) + *(float *)(param_9 + 0x38);
      }
    }
  }
  *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) - *(short *)(param_9 + 0x7c);
  puVar3 = PTR_DAT_80433934;
  iVar5 = *(char *)(param_9 + 400) * 0x3c;
  if (*(int *)(PTR_DAT_80433934 + iVar5 + 0x114) < 1) {
    *(float *)(param_9 + 0x17c) = FLOAT_80436bc4;
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x170) = 1;
    *(float *)(param_9 + 0x17c) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(puVar3 + iVar5 + 0x118) ^ 0x80000000) -
                DOUBLE_80436bd0) /
         (float)((double)CONCAT44(0x43300000,*(uint *)(puVar3 + iVar5 + 0x114) ^ 0x80000000) -
                DOUBLE_80436bd0);
    iVar7 = *(int *)(puVar3 + iVar5 + 0x118);
    if (*(int *)(param_9 + 0x184) != iVar7) {
      if (iVar7 != *(int *)(param_9 + 0x18c)) {
        *(int *)(param_9 + 0x18c) = iVar7;
        uVar10 = *(int *)(param_9 + 0x184) - *(int *)(puVar3 + iVar5 + 0x118);
        uVar8 = (int)uVar10 >> 0x1f;
        iVar7 = (uVar8 ^ uVar10) - uVar8;
        if (iVar7 < 0x3d) {
          *(undefined4 *)(param_9 + 0x188) = 1;
        }
        else {
          iVar7 = iVar7 / 0x3c + (iVar7 >> 0x1f);
          *(int *)(param_9 + 0x188) = (iVar7 - (iVar7 >> 0x1f)) + 1;
        }
      }
      iVar7 = *(int *)(param_9 + 0x184);
      iVar9 = *(int *)(puVar3 + iVar5 + 0x118);
      if (iVar7 < iVar9) {
        iVar13 = iVar9 - iVar7;
        if (*(int *)(param_9 + 0x188) < iVar9 - iVar7) {
          iVar13 = *(int *)(param_9 + 0x188);
        }
        *(int *)(param_9 + 0x184) = *(int *)(param_9 + 0x184) + iVar13;
      }
      else {
        iVar13 = iVar7 - iVar9;
        if (*(int *)(param_9 + 0x188) < iVar7 - iVar9) {
          iVar13 = *(int *)(param_9 + 0x188);
        }
        *(int *)(param_9 + 0x184) = *(int *)(param_9 + 0x184) - iVar13;
      }
      dVar16 = DOUBLE_80436bd0;
      pfVar11 = (float *)0x43300000;
      uVar8 = *(uint *)(param_9 + 0x184) ^ 0x80000000;
      *(float *)(param_9 + 0x180) =
           (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_80436bd0) /
           (float)((double)CONCAT44(0x43300000,*(uint *)(puVar3 + iVar5 + 0x114) ^ 0x80000000) -
                  DOUBLE_80436bd0);
      iVar5 = *(int *)(param_9 + 0x184);
      if (999999 < *(int *)(param_9 + 0x184)) {
        iVar5 = 999999;
      }
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      bVar2 = false;
      iVar7 = 100000;
      iVar13 = param_9 + 0x144;
      for (iVar9 = 0; iVar9 < 6; iVar9 = iVar9 + 1) {
        if ((!bVar2) && ((iVar5 / iVar7 != 0 || (iVar7 == 1)))) {
          bVar2 = true;
          *(char *)(param_9 + 0x1b) = '\x06' - (char)iVar9;
        }
        dVar15 = DOUBLE_80436bd0;
        iVar12 = *(int *)(iVar13 + 8);
        if (bVar2) {
          *(undefined1 *)(iVar12 + 0x10) = 1;
          uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                                iVar5 / iVar7 ^ 0x80000000) - dVar15
                                              ),dVar16,param_3,param_4,param_5,param_6,param_7,
                               param_8,DAT_804361fc,iVar12,pfVar11,uVar8,in_r7,in_r8,in_r9,in_r10);
          zz_0007c30_(uVar14,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,iVar12,
                      extraout_r4,pfVar11,uVar8,in_r7,in_r8,in_r9,in_r10);
        }
        else {
          *(undefined1 *)(iVar12 + 0x10) = 0;
        }
        iVar13 = iVar13 + 4;
        iVar12 = iVar7 / 10 + (iVar7 >> 0x1f);
        iVar5 = iVar5 - (iVar5 / iVar7) * iVar7;
        iVar7 = iVar12 - (iVar12 >> 0x1f);
      }
      iVar7 = *(int *)(param_9 + 0xe0);
      dVar15 = (double)(float)((double)CONCAT44(0x43300000,
                                                (int)*(char *)(param_9 + 0x1b) ^ 0x80000000) -
                              DOUBLE_80436bd0);
      iVar5 = iVar7;
      zz_0008614_(dVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,iVar7,
                  pfVar11,uVar8,in_r7,in_r8,in_r9,in_r10);
      zz_0007c30_(dVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,iVar5,pfVar11,
                  uVar8,in_r7,in_r8,in_r9,in_r10);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4824-4961 ==== */
// ==== 80012984  zz_0012984_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_0012984_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_9 + 0x12) == '\0') {
    dVar9 = (double)FLOAT_80436bd8;
    param_11 = &local_58;
    local_58 = FLOAT_80436bd8;
    local_54 = FLOAT_80436bdc;
    local_50 = FLOAT_80436bc4;
    iVar5 = *(int *)(param_9 + 0xe4);
    uVar8 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),param_11,param_11);
    zz_0007834_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58,
                (char *)param_11,param_12,param_13,param_14,param_15,param_16);
    iVar2 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar2);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    cVar1 = *(char *)(param_9 + 400);
    iVar2 = (int)*(char *)(param_9 + 0x12);
    if ((double)FLOAT_80436be0 < (double)*(float *)(param_9 + 0x17c)) {
      iVar6 = *(int *)(param_9 + 0x144);
      zz_020b520_((double)*(float *)(param_9 + 0x17c),(double)FLOAT_80436bcc,(double)FLOAT_80436bcc,
                  (float *)(param_9 + 0x114),afStack_4c);
      iVar5 = iVar2 * 8;
      dVar10 = (double)FLOAT_80436bc4;
      param_12 = &DAT_802c46a8;
      param_11 = (float *)(&DAT_802c46a8 + iVar5);
      dVar9 = (double)*(float *)(&DAT_802c46ac + iVar5);
      uVar8 = zz_020b4ac_((double)*(float *)(&DAT_802c46a8 + iVar5),dVar9,dVar10,afStack_4c,
                          afStack_4c);
      zz_00076d0_(uVar8,dVar9,dVar10,param_4,param_5,param_6,param_7,param_8,iVar6,afStack_4c,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar5 = zz_0011ce0_(*(int *)(iVar6 + 0x14));
      zz_0009958_(iVar6,iVar5);
    }
    if (*(int *)(param_9 + 0x184) != *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118)) {
      iVar5 = *(int *)(param_9 + 0x148);
      local_50 = FLOAT_80436bc4;
      local_54 = FLOAT_80436bc4;
      zz_020b520_((double)(*(float *)(param_9 + 0x180) - *(float *)(param_9 + 0x17c)),
                  (double)FLOAT_80436bcc,(double)FLOAT_80436bcc,(float *)(param_9 + 0x114),
                  afStack_4c);
      if (iVar2 == 0) {
        dVar9 = (double)_DAT_802c46ac;
        dVar10 = (double)FLOAT_80436bc4;
        uVar8 = zz_020b4ac_((double)(FLOAT_80436be4 * *(float *)(param_9 + 0x17c) + _DAT_802c46a8),
                            dVar9,dVar10,afStack_4c,afStack_4c);
      }
      else {
        dVar9 = (double)*(float *)(&DAT_802c46ac + iVar2 * 8);
        dVar10 = (double)FLOAT_80436bc4;
        uVar8 = zz_020b4ac_(-(double)(FLOAT_80436be4 * *(float *)(param_9 + 0x17c) -
                                     *(float *)(&DAT_802c46a8 + iVar2 * 8)),dVar9,dVar10,afStack_4c,
                            afStack_4c);
      }
      zz_00076d0_(uVar8,dVar9,dVar10,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_4c,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar6 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
      zz_0009958_(iVar5,iVar6);
    }
    iVar5 = *(int *)(param_9 + 0xe0);
    if (iVar2 == 0) {
      local_58 = FLOAT_80436be4 * *(float *)(param_9 + 0x180) + _DAT_802c46a8;
      local_54 = FLOAT_80436be8;
    }
    else {
      local_58 = -(FLOAT_80436be4 * *(float *)(param_9 + 0x180) -
                  *(float *)(&DAT_802c46a8 + iVar2 * 8));
      local_54 = FLOAT_80436bec;
    }
    pfVar4 = &local_58;
    local_50 = FLOAT_80436bc4;
    gnt4_PSVECAdd_bl(pfVar4,(float *)(param_9 + 0x20),pfVar4);
    dVar9 = (double)local_54;
    dVar10 = (double)local_50;
    uVar8 = gnt4_PSMTXTrans_bl((double)local_58,dVar9,dVar10,afStack_4c);
    zz_00076d0_(uVar8,dVar9,dVar10,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_4c,
                (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
    iVar6 = zz_0011ce0_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar6);
    iVar5 = iVar2 * 0xc;
    dVar10 = (double)FLOAT_80436bc4;
    dVar9 = (double)*(float *)(&DAT_802c46bc + iVar5);
    uVar8 = zz_020b4ac_((double)*(float *)(&DAT_802c46b8 + iVar5),dVar10,dVar9,afStack_4c,afStack_4c
                       );
    if (iVar2 == 1) {
      param_12 = (undefined *)0x43300000;
      dVar10 = (double)FLOAT_80436bc4;
      uStack_14 = (int)*(char *)(param_9 + 0x1b) ^ 0x80000000;
      pfVar4 = (float *)0x802c46c4;
      local_18 = 0x43300000;
      dVar9 = dVar10;
      param_4 = DOUBLE_80436bd0;
      uVar8 = zz_020b4ac_(-(double)((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80436bd0
                                           ) * fRam802c46cc),dVar10,dVar10,afStack_4c,afStack_4c);
    }
    iVar6 = param_9 + 0x158;
    iVar2 = 5;
    do {
      iVar7 = *(int *)(iVar6 + 8);
      zz_00076d0_(uVar8,dVar10,dVar9,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_4c,
                  (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
      iVar3 = zz_0011ce0_(*(int *)(iVar7 + 0x14));
      zz_0009958_(iVar7,iVar3);
      dVar10 = (double)FLOAT_80436bc4;
      dVar9 = dVar10;
      uVar8 = zz_020b4ac_((double)*(float *)(&DAT_802c46c0 + iVar5),dVar10,dVar10,afStack_4c,
                          afStack_4c);
      iVar2 = iVar2 + -1;
      iVar6 = iVar6 + -4;
    } while (-1 < iVar2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4965-5023 ==== */
// ==== 80012d08  zz_0012d08_ ====

void zz_0012d08_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  
  iVar4 = DAT_804361fc;
  if (PTR_DAT_80433934[0x50] == '\0') {
    *(code **)(param_9 + 0x100) = FUN_80012274;
    zz_0089100_(param_9,0x21,1);
    fVar1 = FLOAT_80436bf0;
    *(undefined1 *)(param_9 + 0x84) = 9;
    fVar2 = FLOAT_80436bf4;
    *(float *)(param_9 + 100) = fVar1;
    fVar3 = FLOAT_80436bf8;
    dVar5 = (double)FLOAT_80436bf8;
    *(float *)(param_9 + 0x68) = fVar2;
    fVar1 = FLOAT_80436bc4;
    *(float *)(param_9 + 0x6c) = fVar3;
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(float *)(param_9 + 0x16c) = fVar1;
    *(float *)(param_9 + 0x168) = fVar1;
    *(float *)(param_9 + 0x164) = fVar1;
    *(undefined4 *)(*(int *)(param_9 + 0x14c) + 0x14) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_9 + 0x148) + 0x14) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_9 + 0x144) + 0x14) = 0xffffffff;
    *(undefined1 *)(param_9 + 0x192) = 0xff;
    *(undefined1 *)(param_9 + 0x191) = 0xff;
    *(undefined1 *)(param_9 + 400) = 0xff;
    uVar6 = zz_0006fb4_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                        *(int *)(param_9 + 0x15c),0xf,param_12,param_13,param_14,param_15,param_16);
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0x160),0xe,param_12,param_13,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x188) = 0;
    iVar4 = *(int *)(PTR_DAT_80433934 + 0x4c) - *(int *)(param_9 + 0x188);
    if (iVar4 < 0x51) {
      *(undefined4 *)(param_9 + 0x18c) = 1;
    }
    else {
      iVar4 = iVar4 / 0x50 + (iVar4 >> 0x1f);
      *(int *)(param_9 + 0x18c) = (iVar4 - (iVar4 >> 0x1f)) + 1;
    }
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5027-5035 ==== */
// ==== 80012e4c  zz_0012e4c_ ====

void zz_0012e4c_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  FUN_80012e74(param_1,-0x7fd3c480,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5039-5171 ==== */
// ==== 80012e74  FUN_80012e74 ====

/* WARNING: Removing unreachable block (ram,0x8001319c) */
/* WARNING: Removing unreachable block (ram,0x80012e84) */

void FUN_80012e74(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  float *pfVar10;
  int *piVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar17;
  double local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  iVar5 = *(int *)(PTR_DAT_80433934 + 0x4c);
  if (*(char *)(param_1 + 0x19) == '\0') {
    iVar5 = *(int *)(param_1 + 0x188);
    if (*(int *)(param_1 + 0x18c) != 0) {
      iVar1 = *(int *)(PTR_DAT_80433934 + 0x48);
      iVar5 = *(int *)(param_1 + 0x188) + *(int *)(param_1 + 0x18c);
      if (iVar1 <= iVar5) {
        *(undefined4 *)(param_1 + 0x18c) = 0;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        iVar5 = iVar1;
      }
    }
  }
  local_58 = (double)(CONCAT44(0x43300000,iVar5) ^ 0x80000000);
  local_50 = (double)CONCAT44(0x43300000,*(uint *)(PTR_DAT_80433934 + 0x48) ^ 0x80000000);
  *(short *)(param_1 + 0x74) =
       (short)(int)-(FLOAT_80436bfc *
                     ((float)(local_58 - DOUBLE_80436bd0) / (float)(local_50 - DOUBLE_80436bd0)) -
                    FLOAT_80436bfc);
  if (*(int *)(param_1 + 0x188) != iVar5) {
    *(int *)(param_1 + 0x188) = iVar5;
    iVar5 = iVar5 / 0x3c + (iVar5 >> 0x1f);
    iVar5 = iVar5 - (iVar5 >> 0x1f);
    if (999 < iVar5) {
      iVar5 = 999;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    if (((*(char *)(param_1 + 0x19) == '\0') || (0x1d < iVar5)) ||
       ((*(ushort *)(param_1 + 0x1c) & 8) == 0)) {
      *(undefined1 *)(param_1 + 0x193) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x193) = 1;
    }
    iVar1 = *(int *)(param_1 + 0x160);
    local_48 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x193)) ^ 0x80000000);
    dVar16 = (double)(float)(local_48 - DOUBLE_80436bd0);
    dVar13 = DOUBLE_80436c00 * DOUBLE_80436c08 * dVar16;
    dVar14 = (double)(longlong)(int)(DOUBLE_80436c00 * dVar16);
    dVar17 = (double)(float)((double)FLOAT_80436c14 * dVar16 + (double)FLOAT_80436c10);
    dVar15 = DOUBLE_80436c00;
    zz_0007cd0_(iVar1,(int)(DOUBLE_80436c00 * dVar16) & 0xff,(int)dVar13 & 0xff,0);
    uVar12 = zz_0007cac_(dVar17,iVar1);
    iVar1 = 0;
    for (psVar2 = &DAT_802c3b68; iVar5 < *psVar2; psVar2 = psVar2 + 4) {
      iVar1 = iVar1 + 1;
    }
    iVar6 = iVar1 * 6;
    pfVar4 = (float *)(iVar1 * 8);
    piVar11 = (int *)(param_1 + 0x144);
    pfVar10 = pfVar4 + -0x1ff4f126;
    iVar1 = iVar1 * 0x18;
    iVar8 = 0;
    uVar9 = 100;
    do {
      piVar11[0xe] = param_2 + iVar1;
      iVar3 = (int)*(short *)((int)pfVar10 + 2);
      if (*(int *)(*piVar11 + 0x14) != iVar3) {
        *(int *)(piVar11[3] + 0x14) = iVar3;
        *(int *)(*piVar11 + 0x14) = iVar3;
        pfVar4 = *(float **)(*piVar11 + 0x14);
        if (-1 < (int)pfVar4) {
          uVar12 = zz_0006fb4_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,DAT_804361fc,
                               *piVar11,(int)pfVar4,iVar6,param_5,param_6,param_7,param_8);
          pfVar4 = (float *)(*(int *)(*piVar11 + 0x14) + 4);
          uVar12 = zz_0006fb4_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,DAT_804361fc,
                               piVar11[3],(int)pfVar4,iVar6,param_5,param_6,param_7,param_8);
        }
      }
      dVar17 = DOUBLE_80436bd0;
      if (-1 < *(int *)(*piVar11 + 0x14)) {
        uVar7 = iVar5 / (int)uVar9;
        if (*(char *)(param_1 + iVar8 + 400) != (char)uVar7) {
          local_48 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
          *(char *)(param_1 + iVar8 + 400) = (char)uVar7;
          zz_00086b8_((double)(float)(local_48 - dVar17),dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,
                      in_f8,DAT_804361fc,*piVar11,pfVar4,iVar6,param_5,param_6,param_7,param_8);
          local_50 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
          uVar12 = zz_00086b8_((double)(float)(local_50 - DOUBLE_80436bd0),dVar13,dVar14,dVar15,
                               dVar16,in_f6,in_f7,in_f8,DAT_804361fc,piVar11[3],pfVar4,iVar6,param_5
                               ,param_6,param_7,param_8);
          uVar12 = zz_0007c30_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,*piVar11,
                               extraout_r4,pfVar4,iVar6,param_5,param_6,param_7,param_8);
          uVar12 = zz_0007c30_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,piVar11[3],
                               extraout_r4_00,pfVar4,iVar6,param_5,param_6,param_7,param_8);
        }
      }
      iVar8 = iVar8 + 1;
      iVar1 = iVar1 + 8;
      piVar11 = piVar11 + 1;
      pfVar10 = (float *)((int)pfVar10 + 2);
      iVar3 = (iVar5 / (int)uVar9) * uVar9;
      uVar9 = uVar9 / 10;
      iVar5 = iVar5 - iVar3;
    } while (iVar8 < 3);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5175-5233 ==== */
// ==== 800131b8  zz_00131b8_ ====

void zz_00131b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [12];
  float afStack_4c [15];
  
  iVar3 = *(int *)(param_9 + 0x15c);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  iVar3 = *(int *)(param_9 + 0x160);
  pfVar2 = &local_88;
  local_88 = FLOAT_80436bc4;
  local_84 = FLOAT_80436bc4;
  local_80 = FLOAT_80436c18;
  uVar6 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_0007834_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_88,
              (char *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  iVar1 = 0;
  piVar5 = (int *)(param_9 + 0x144);
  do {
    if (-1 < *(int *)(*piVar5 + 0x14)) {
      iVar4 = *(int *)(param_9 + (iVar1 + *(char *)(param_9 + 0x193) * 3) * 4 + 0x144);
      gnt4_PSMTXTrans_bl((double)*(float *)piVar5[0xe],(double)((float *)piVar5[0xe])[1],
                         (double)FLOAT_80436bc8,afStack_4c);
      dVar7 = (double)FLOAT_80436c1c;
      dVar8 = (double)FLOAT_80436bcc;
      gnt4_PSMTXScale_bl(dVar7,dVar7,dVar8,afStack_7c);
      pfVar2 = afStack_4c;
      uVar6 = gnt4_PSMTXConcat_bl(pfVar2,afStack_7c,pfVar2);
      zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_4c,
                  (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
      iVar3 = zz_0011ce0_(*(int *)(iVar4 + 0x14));
      zz_0009958_(iVar4,iVar3);
    }
    iVar1 = iVar1 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar1 < 3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5237-5279 ==== */
// ==== 80013304  zz_0013304_ ====

void zz_0013304_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  double dVar3;
  undefined8 uVar4;
  
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar1 = FLOAT_80436c20;
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar2 = FLOAT_80436c24;
  dVar3 = (double)FLOAT_80436c24;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_80436c28;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  uVar4 = zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),7,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe4),8,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe8),10,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x144),6,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x148),0xb,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x14c),0xb,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x150),0xc,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x154),0xc,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x158),0xc,param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5283-5356 ==== */
// ==== 800133f4  zz_00133f4_ ====

/* WARNING: Removing unreachable block (ram,0x800135e4) */
/* WARNING: Removing unreachable block (ram,0x800135dc) */
/* WARNING: Removing unreachable block (ram,0x8001340c) */
/* WARNING: Removing unreachable block (ram,0x80013404) */

void zz_00133f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float afStack_a8 [12];
  float afStack_78 [12];
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  iVar3 = *(int *)(param_9 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  dVar7 = (double)FLOAT_80436c2c;
  dVar9 = (double)((float)(dVar7 * (double)*(float *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] +
                                                     0x20)) / *(float *)(DAT_8043625c + 0x38));
  local_48 = 0x43300000;
  uStack_44 = 0x10000U - (int)(short)(&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2] ^
              0x80000000;
  dVar8 = (double)(-(float)(dVar7 * (double)*(float *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] +
                                                      0x28)) / *(float *)(DAT_8043625c + 0x40));
  iVar4 = *(int *)(param_9 + 0xe4);
  iVar1 = DAT_8043625c;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80436c30 *
                              (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80436bd0)),
                      afStack_a8,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_a8,afStack_a8);
  dVar6 = (double)FLOAT_80436c34;
  gnt4_PSMTXTrans_bl(dVar9,dVar8,dVar6,afStack_78);
  pfVar2 = afStack_78;
  uVar5 = gnt4_PSMTXConcat_bl(afStack_a8,pfVar2,pfVar2);
  zz_00076d0_(uVar5,dVar8,dVar6,dVar7,param_5,param_6,param_7,param_8,iVar4,afStack_78,
              (undefined *)pfVar2,iVar1,param_13,param_14,param_15,param_16);
  iVar3 = zz_0011ce0_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar3);
  iVar3 = *(int *)(param_9 + 0xe8);
  dVar6 = (double)FLOAT_80436bcc;
  gnt4_PSMTXTrans_bl((double)FLOAT_80436bc4,(double)FLOAT_80436bc4,dVar6,afStack_78);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_78,afStack_78);
  local_40 = 0x43300000;
  dVar8 = (double)FLOAT_80436c30;
  uStack_3c = 0x10000U - (int)(short)(&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2] ^
              0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uStack_3c)
                                                             - DOUBLE_80436bd0)),afStack_a8,0x7a);
  pfVar2 = afStack_78;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar2,afStack_a8,pfVar2);
  zz_00076d0_(uVar5,dVar8,dVar6,dVar7,param_5,param_6,param_7,param_8,iVar3,afStack_78,
              (undefined *)pfVar2,iVar1,param_13,param_14,param_15,param_16);
  iVar1 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  return;
}
