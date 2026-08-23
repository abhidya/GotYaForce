#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80131b0c(int param_1);
void zz_0131c14_(int param_1,undefined1 param_2);
void FUN_80131d24(int param_1);
void FUN_80131d78(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5 ,double param_6,double param_7,double param_8,int param_9);
void zz_0131ecc_(int param_1);
void FUN_8013202c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_8013204c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
undefined4 zz_013212c_(int param_1,int param_2,undefined4 param_3);

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0035.c 751-782 ==== */
// ==== 80131b0c  FUN_80131b0c ====

void FUN_80131b0c(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                           DOUBLE_80439e88) * FLOAT_80439e80);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439e9c,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_80439ea8 + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 786-819 ==== */
// ==== 80131c14  zz_0131c14_ ====

void zz_0131c14_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x305) || (sVar1 == 0x309)) || (sVar1 == 0x30a)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_80131d24;
    *(code **)(puVar2 + 0x10c) = FUN_8013204c;
    *(int *)(puVar2 + 0x8c) = param_1;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar2[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar2[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar2[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 823-831 ==== */
// ==== 80131d24  FUN_80131d24 ====

void FUN_80131d24(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80336550)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 835-899 ==== */
// ==== 80131d78  FUN_80131d78 ====

void FUN_80131d78(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  
  iVar6 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar6;
  iVar7 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar4 = *(char *)(param_9 + 0x11) * 0x18;
  zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80439eb0;
  dVar10 = (double)FLOAT_80439eb0;
  *(undefined1 *)(param_9 + 0x84) = 0x57;
  fVar2 = FLOAT_80439eb4;
  *(undefined *)(param_9 + 0x89) = (&DAT_80336461)[iVar4];
  uVar3 = *(undefined4 *)(&DAT_80336468 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80336464 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033646c + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80336470 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80336474 + iVar4);
  *(char *)(param_9 + 0x12) = (char)*(undefined2 *)(&DAT_80336476 + iVar4);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  dVar8 = (double)*(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x144) = *(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x148) = fVar2;
  *(float *)(param_9 + 0x14c) = fVar2;
  *(float *)(param_9 + 0x150) = fVar1;
  iVar7 = zz_0006f98_(iVar7);
  uVar9 = zz_0007030_(dVar8,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_80336460)[iVar4],iVar7 + 0xc28,iVar6,in_r8,in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  iVar4 = (int)(char)(&DAT_80336460)[iVar4];
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,iVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
              extraout_r4,iVar4,iVar5,iVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439eb8,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0131ecc_(param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 903-969 ==== */
// ==== 80131ecc  zz_0131ecc_ ====

void zz_0131ecc_(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x11);
  iVar4 = *(int *)(param_1 + 0x90);
  if (cVar1 == '\x03') {
LAB_80131f34:
    if (-1 < *(char *)(iVar4 + 0x6e8)) {
      if (*(char *)(iVar4 + 0x6e8) == '\x01') {
        if ((*(byte *)(iVar4 + 0x6e9) & *(byte *)(param_1 + 0x12)) == 0) {
          *(float *)(param_1 + 0x14c) = FLOAT_80439eb4;
        }
        else if (*(float *)(param_1 + 0x148) < FLOAT_80439eb0) {
          *(float *)(param_1 + 0x14c) = FLOAT_80439ec0;
        }
      }
      else {
        *(float *)(param_1 + 0x14c) = FLOAT_80439eb4;
      }
    }
    dVar3 = DOUBLE_80439ed0;
    *(float *)(param_1 + 0x148) =
         (float)(DOUBLE_80439ec8 *
                 (double)(float)((double)*(float *)(param_1 + 0x14c) -
                                (double)*(float *)(param_1 + 0x148)) +
                (double)*(float *)(param_1 + 0x148));
    if ((dVar3 <= (double)*(float *)(param_1 + 0x148)) &&
       (FLOAT_80439eb0 < *(float *)(param_1 + 0x14c))) {
      *(float *)(param_1 + 0x14c) = FLOAT_80439eb0;
    }
  }
  else {
    if (cVar1 < '\x03') {
      if (cVar1 == '\0') goto LAB_80131f34;
      if (cVar1 < '\0') goto LAB_80132000;
    }
    else {
      if ('\t' < cVar1) goto LAB_80132000;
      if ('\a' < cVar1) {
        if ((*(char *)(iVar4 + 0x6e8) < '\x01') || ((*(byte *)(iVar4 + 0x6e9) & 4) == 0)) {
          *(float *)(param_1 + 0x150) = FLOAT_80439eb0;
        }
        else {
          *(float *)(param_1 + 0x150) = FLOAT_80439ebc;
        }
        goto LAB_80131f34;
      }
    }
    *(float *)(param_1 + 0x148) = FLOAT_80439eb4;
    if ((*(byte *)(iVar4 + 0x144) & *(byte *)(param_1 + 0x12)) != 0) {
      *(float *)(param_1 + 0x148) = FLOAT_80439eb0;
    }
  }
LAB_80132000:
  fVar2 = *(float *)(param_1 + 0x144) * *(float *)(param_1 + 0x148);
  *(float *)(param_1 + 0x60) = fVar2;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 973-981 ==== */
// ==== 8013202c  FUN_8013202c ====

void FUN_8013202c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 985-1026 ==== */
// ==== 8013204c  FUN_8013204c ====

void FUN_8013204c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  if (FLOAT_80439eb4 < *(float *)(param_1 + 0x58)) {
    cVar1 = *(char *)(param_1 + 0x11);
    if ((*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') &&
       (*(char *)(*(int *)(param_1 + 0x90) + 0x3ec) != '\x04')) {
      iVar4 = *(int *)(param_1 + 0xe0);
      iVar3 = 0;
    }
    else {
      iVar4 = *(int *)(param_1 + 0xe4);
      iVar3 = 1;
    }
    dVar5 = (double)FLOAT_80439eb0;
    dVar7 = (double)*(float *)(param_1 + 0x150);
    gnt4_PSMTXScale_bl(dVar5,dVar5,dVar7,afStack_48);
    pfVar2 = afStack_48;
    uVar6 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
    zz_00076d0_(uVar6,dVar5,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,iVar4,afStack_48,(undefined *)pfVar2
                ,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(iVar4,(int)(char)(&DAT_80336462)[cVar1 * 0x18 + iVar3]);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1030-1086 ==== */
// ==== 8013212c  zz_013212c_ ====

undefined4 zz_013212c_(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  
  iVar2 = param_2 * 2;
  cVar1 = (&DAT_80336b20)[iVar2];
  if (*(short *)(param_1 + 1000) == *(short *)(&DAT_80336928 + (char)(&DAT_80336b21)[iVar2] * 0x28))
  {
    puVar4 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar4 == (undefined1 *)0x0) {
      uVar3 = 0;
    }
    else {
      *puVar4 = 1;
      puVar4[0x13] = (char)param_2;
      puVar4[0x11] = (&DAT_80336b20)[iVar2];
      puVar4[0x12] = (&DAT_80336b21)[iVar2];
      puVar4[0x10] = 0x24;
      *(code **)(puVar4 + 0xc) = FUN_801322dc;
      *(code **)(puVar4 + 0x10c) = FUN_80133530;
      *(int *)(puVar4 + 0x8c) = param_1;
      *(undefined4 *)(puVar4 + 0x90) = *(undefined4 *)(param_1 + 0x90);
      *(undefined2 *)(puVar4 + 0x94) = *(undefined2 *)(param_1 + 0x94);
      puVar4[0x96] = *(undefined1 *)(param_1 + 0x96);
      puVar4[0x97] = *(undefined1 *)(param_1 + 0x97);
      puVar4[0x88] = *(undefined1 *)(param_1 + 0x88);
      *(undefined4 *)(puVar4 + 200) = *(undefined4 *)(param_1 + 200);
      *(undefined4 *)(puVar4 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
      *(undefined4 *)(puVar4 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(puVar4 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
      *(undefined4 *)(puVar4 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
      puVar4[0xd0] = *(undefined1 *)(param_1 + 0xd0);
      *(undefined4 *)(puVar4 + 0x148) = *(undefined4 *)(puVar4 + 0xcc);
      *(undefined4 *)(puVar4 + 0x144) = *(undefined4 *)(puVar4 + 200);
      puVar4[0x16b] = puVar4[0xd0];
      zz_00f036c_(param_1,7);
      uVar3 = 0x8444;
      puVar4[0x168] = (&DAT_80336563)[cVar1 * 0x24];
      *(undefined4 *)(puVar4 + 0x164) = param_3;
      **(byte **)(puVar4 + 0x164) = **(byte **)(puVar4 + 0x164) & ~puVar4[0x168];
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}
