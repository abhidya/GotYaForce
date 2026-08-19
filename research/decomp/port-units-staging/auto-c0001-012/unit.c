#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0013608_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0013690_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_00139e0_(int param_1);
void zz_0013a28_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0013d80_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0013e54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0013f3c_(int param_1);
void zz_0013f80_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5360-5389 ==== */
// ==== 80013608  zz_0013608_ ====

void zz_0013608_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  *(undefined1 *)(param_9 + 0x84) = 9;
  fVar2 = FLOAT_80436c24;
  dVar3 = (double)FLOAT_80436c24;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_80436c38;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  uVar4 = zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0x158),6,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x15c),9,param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5393-5515 ==== */
// ==== 80013690  zz_0013690_ ====

/* WARNING: Removing unreachable block (ram,0x800139c4) */
/* WARNING: Removing unreachable block (ram,0x800139bc) */
/* WARNING: Removing unreachable block (ram,0x800136a8) */
/* WARNING: Removing unreachable block (ram,0x800136a0) */

void zz_0013690_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  int in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  float afStack_b8 [12];
  float afStack_88 [12];
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  puVar6 = &DAT_803c73b0;
  puVar5 = &DAT_803c4e84;
  local_58 = 0x43300000;
  dVar15 = (double)FLOAT_80436c30;
  iVar9 = (&DAT_803c4e84)[(char)(&DAT_803c7695)[(char)PTR_DAT_80433930[0x28] * 0x3e4]];
  uStack_54 = (int)(short)(*(short *)(iVar9 + 0x72) -
                          (&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2]) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_54
                                                                               ) - DOUBLE_80436bd0))
                      ,afStack_88,0x7a);
  pfVar3 = afStack_88;
  uVar14 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar3,pfVar3);
  iVar7 = *(int *)(param_9 + 0x158);
  zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_88,
              (undefined *)pfVar3,puVar5,puVar6,in_r8,in_r9,in_r10);
  iVar2 = zz_0011ce0_(*(int *)(iVar7 + 0x14));
  uVar14 = zz_0009958_(iVar7,iVar2);
  iVar7 = *(int *)(param_9 + 0x15c);
  zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_88,
              (undefined *)pfVar3,puVar5,puVar6,in_r8,in_r9,in_r10);
  iVar2 = zz_0011ce0_(*(int *)(iVar7 + 0x14));
  uVar14 = zz_0009958_(iVar7,iVar2);
  iVar2 = 0;
  cVar1 = *(char *)(iVar9 + 0x88);
  uVar8 = 1 << (int)*(char *)(iVar9 + 0x3e4) & 0xff;
  piVar13 = &DAT_803c4e6c;
  piVar12 = (int *)(param_9 + 0x144);
  iVar7 = 0;
  while ((iVar7 < DAT_80436260 && (iVar2 < 5))) {
    iVar10 = *piVar13;
    if (((uVar8 & 1 << (int)*(char *)(iVar10 + 0x3e4)) == 0) && (*(char *)(iVar10 + 0x18) == '\x01')
       ) {
      iVar11 = *piVar12;
      if (*(char *)(iVar10 + 0x88) == cVar1) {
        iVar4 = 0xb;
      }
      else if (*(char *)(iVar10 + 0x88) == '\x02') {
        iVar4 = 0xd;
      }
      else {
        iVar4 = 0xc;
      }
      zz_0006fb4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,iVar11,
                  iVar4,puVar5,puVar6,in_r8,in_r9,in_r10);
      param_4 = (double)FLOAT_80436c2c;
      puVar6 = (undefined1 *)((char)PTR_DAT_80433930[0x28] * 0x3e4);
      dVar16 = (double)((float)(param_4 *
                               -(double)(*(float *)(iVar10 + 0x20) - *(float *)(iVar9 + 0x20))) /
                       *(float *)(DAT_8043625c + 0x38));
      local_58 = 0x43300000;
      dVar15 = (double)((float)(param_4 *
                               (double)(*(float *)(iVar10 + 0x28) - *(float *)(iVar9 + 0x28))) /
                       *(float *)(DAT_8043625c + 0x40));
      uStack_54 = (int)(short)-(&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2] ^ 0x80000000;
      in_r8 = DAT_8043625c;
      gnt4_PSMTXRotRad_bl((double)(FLOAT_80436c30 *
                                  (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436bd0))
                          ,afStack_b8,0x7a);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_b8,afStack_b8);
      param_3 = (double)FLOAT_80436c34;
      gnt4_PSMTXTrans_bl(dVar16,dVar15,param_3,afStack_88);
      gnt4_PSMTXConcat_bl(afStack_b8,afStack_88,afStack_b8);
      local_50 = 0x43300000;
      dVar15 = (double)FLOAT_80436c30;
      puVar5 = (undefined4 *)(&DAT_803c73b0 + (char)PTR_DAT_80433930[0x28] * 0x3e4);
      uStack_4c = (int)(short)(*(short *)(iVar10 + 0x72) -
                              (&DAT_803c7422)[(char)PTR_DAT_80433930[0x28] * 0x1f2]) ^ 0x80000000;
      gnt4_PSMTXRotRad_bl((double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                    uStack_4c) -
                                                                  DOUBLE_80436bd0)),afStack_88,0x7a)
      ;
      pfVar3 = afStack_88;
      uVar14 = gnt4_PSMTXConcat_bl(afStack_b8,pfVar3,pfVar3);
      zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar11,afStack_88,
                  (undefined *)pfVar3,puVar5,puVar6,in_r8,in_r9,in_r10);
      iVar4 = zz_0011ce0_(*(int *)(iVar11 + 0x14));
      uVar14 = zz_0009958_(iVar11,iVar4);
      piVar12 = piVar12 + 1;
      iVar2 = iVar2 + 1;
      uVar8 = uVar8 | 1 << (int)*(char *)(iVar10 + 0x3e4) & 0xffU;
    }
    piVar13 = piVar13 + 1;
    iVar7 = iVar7 + 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5519-5528 ==== */
// ==== 800139e0  zz_00139e0_ ====

void zz_00139e0_(int param_1)

{
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  *(undefined1 *)(param_1 + 0x84) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5532-5712 ==== */
// ==== 80013a28  zz_0013a28_ ====

/* WARNING: Removing unreachable block (ram,0x80013d64) */
/* WARNING: Removing unreachable block (ram,0x80013d5c) */
/* WARNING: Removing unreachable block (ram,0x80013a40) */
/* WARNING: Removing unreachable block (ram,0x80013a38) */

void zz_0013a28_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined1 uVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  char *pcVar5;
  float *pfVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x172) = 0;
    iVar4 = *(int *)(param_9 + 0x90);
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(iVar4 + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(iVar4 + 0x3e4);
    cVar3 = *(char *)(iVar4 + 0x7cd);
    iVar4 = *(int *)(iVar4 + 0x4ac);
    *(char *)(param_9 + 0x17a) = cVar3;
    dVar13 = DOUBLE_80436bd0;
    if (cVar3 == '\0') {
      uVar1 = *(undefined1 *)(iVar4 + 0x9f);
      local_58 = 0x43300000;
      *(undefined1 *)(param_9 + 0x17c) = uVar1;
      dVar16 = (double)FLOAT_80436c40;
      piVar10 = (int *)(param_9 + 0x144);
      *(undefined1 *)(param_9 + 0x17b) = uVar1;
      dVar12 = (double)FLOAT_80436c44;
      uStack_54 = (int)*(char *)(param_9 + 0x17b) - 1U ^ 0x80000000;
      param_2 = (double)(float)(dVar16 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                        dVar13));
      dVar15 = -(double)(float)(param_2 * dVar12 + (double)FLOAT_80436c3c);
      iVar4 = param_9;
      for (uVar7 = 0; (int)uVar7 < (int)*(char *)(param_9 + 0x17b); uVar7 = uVar7 + 1) {
        if ((int)uVar7 < 8) {
          iVar11 = *piVar10;
        }
        else {
          iVar11 = *(int *)(iVar4 + 0xc0);
        }
        pcVar5 = (char *)0x17;
        uVar14 = zz_0006fb4_(dVar12,param_2,dVar13,param_4,param_5,param_6,param_7,param_8,
                             DAT_804361fc,iVar11,0x17,param_12,param_13,param_14,param_15,param_16);
        (&DAT_802c3c3c)[(uVar7 & 1) * 3] = (float)dVar15;
        zz_0007834_(uVar14,param_2,dVar13,param_4,param_5,param_6,param_7,param_8,iVar11,
                    &DAT_802c3c3c + (uVar7 & 1) * 3,pcVar5,param_12,param_13,param_14,param_15,
                    param_16);
        fVar2 = FLOAT_80436c4c;
        if ((uVar7 & 1) != 0) {
          fVar2 = FLOAT_80436c48;
        }
        dVar12 = (double)zz_0007e74_((double)fVar2,param_2,dVar13,param_4,param_5,param_6,param_7,
                                     param_8,iVar11,extraout_r4,pcVar5,param_12,param_13,param_14,
                                     param_15,param_16);
        dVar15 = (double)(float)(dVar15 + dVar16);
        iVar4 = iVar4 + 4;
        piVar10 = piVar10 + 1;
      }
      *(undefined1 *)(param_9 + 0x17c) = 0xff;
      param_3 = dVar13;
    }
    else {
      param_13 = &DAT_802b0988;
      pcVar5 = (char *)0x16;
      local_68 = DAT_802b0988;
      local_64 = DAT_802b098c;
      local_60 = DAT_802b0990;
      param_12 = DAT_802b0988;
      uVar14 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x144),0x16,DAT_802b0988,&DAT_802b0988,
                           param_14,param_15,param_16);
      zz_0007834_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x144),&local_68,pcVar5,param_12,param_13,param_14,param_15,
                  param_16);
    }
  }
  iVar4 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  pfVar6 = *(float **)(iVar4 + 0x4ac);
  *(undefined1 *)(param_9 + 0x170) = 0;
  dVar13 = DOUBLE_80436bd0;
  if ((*(byte *)(iVar4 + 0x7d5) & 1) == 0) {
    if (*(char *)(iVar4 + 0x7cd) == '\0') {
      if (*(char *)(iVar4 + 0x747) == '\0') {
        *(undefined1 *)(param_9 + 0x17c) = 0xff;
      }
      else {
        *(undefined1 *)(param_9 + 0x170) = 1;
        cVar3 = *(char *)(param_9 + 0x17b) - *(char *)(iVar4 + 0x747);
        iVar4 = (int)cVar3;
        if (iVar4 != *(char *)(param_9 + 0x17c)) {
          *(undefined1 *)(param_9 + 0x17d) = 0x1e;
          *(char *)(param_9 + 0x17c) = cVar3;
        }
        if (*(char *)(param_9 + 0x17d) != '\0') {
          *(char *)(param_9 + 0x17d) = *(char *)(param_9 + 0x17d) + -1;
        }
        piVar10 = (int *)(param_9 + 0x144);
        iVar11 = param_9;
        for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x17b); iVar9 = iVar9 + 1) {
          if (iVar9 < 8) {
            iVar8 = *piVar10;
          }
          else {
            iVar8 = *(int *)(iVar11 + 0xc0);
          }
          if (iVar4 < iVar9) {
            dVar13 = (double)FLOAT_80436bcc;
          }
          else if (iVar4 == iVar9) {
            local_58 = 0x43300000;
            uStack_54 = (int)*(char *)(param_9 + 0x17d) ^ 0x80000000;
            param_3 = (double)FLOAT_80436bcc;
            dVar13 = (double)(float)(param_3 -
                                    (double)((float)((double)CONCAT44(0x43300000,uStack_54) -
                                                    DOUBLE_80436bd0) / FLOAT_80436c50));
            param_2 = DOUBLE_80436bd0;
          }
          else {
            dVar13 = (double)FLOAT_80436bc4;
          }
          uVar14 = zz_00086b8_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar8,pfVar6,param_12,param_13,param_14,param_15,
                               param_16);
          zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,
                      extraout_r4_00,pfVar6,param_12,param_13,param_14,param_15,param_16);
          iVar11 = iVar11 + 4;
          piVar10 = piVar10 + 1;
        }
      }
    }
    else {
      uStack_54 = (int)*(short *)(iVar4 + 0x736) ^ 0x80000000;
      local_58 = 0x43300000;
      uStack_4c = (int)*(short *)(pfVar6 + 1) ^ 0x80000000;
      dVar16 = (double)FLOAT_80436bcc;
      dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80436bd0);
      local_50 = 0x43300000;
      dVar12 = (double)(float)(dVar16 - (double)(float)(dVar15 / (double)(float)((double)CONCAT44(
                                                  0x43300000,uStack_4c) - DOUBLE_80436bd0)));
      if ((double)FLOAT_80436bc4 != dVar12) {
        iVar4 = *(int *)(param_9 + 0x144);
        *(undefined1 *)(param_9 + 0x170) = 1;
        uVar14 = zz_00086b8_(dVar12,dVar15,dVar13,dVar16,param_5,param_6,param_7,param_8,
                             DAT_804361fc,iVar4,pfVar6,param_12,param_13,param_14,param_15,param_16)
        ;
        zz_0007c30_(uVar14,dVar15,dVar13,dVar16,param_5,param_6,param_7,param_8,iVar4,extraout_r4_01
                    ,pfVar6,param_12,param_13,param_14,param_15,param_16);
      }
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5716-5760 ==== */
// ==== 80013d80  zz_0013d80_ ====

void zz_0013d80_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_0013a28_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96));
  if ((uVar1 == 0) && (*(char *)(param_9 + 0x170) != '\0')) {
    if (*(char *)(param_9 + 0x17a) == '\0') {
      piVar5 = (int *)(param_9 + 0x144);
      iVar6 = param_9;
      for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x17b); iVar3 = iVar3 + 1) {
        if (iVar3 < 8) {
          iVar4 = *piVar5;
        }
        else {
          iVar4 = *(int *)(iVar6 + 0xc0);
        }
        iVar2 = zz_0011ce0_(*(int *)(iVar4 + 0x14));
        zz_0009958_(iVar4,iVar2);
        iVar6 = iVar6 + 4;
        piVar5 = piVar5 + 1;
      }
    }
    else {
      iVar3 = *(int *)(param_9 + 0x144);
      iVar6 = zz_0011ce0_(*(int *)(iVar3 + 0x14));
      zz_0009958_(iVar3,iVar6);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5764-5809 ==== */
// ==== 80013e54  zz_0013e54_ ====

void zz_0013e54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  undefined8 uVar5;
  
  *(code **)(param_9 + 0x100) = FUN_80012274;
  zz_0089100_(param_9,0x21,1);
  fVar1 = FLOAT_80436c54;
  *(undefined1 *)(param_9 + 0x84) = 5;
  fVar3 = FLOAT_80436c58;
  *(float *)(param_9 + 100) = fVar1;
  fVar2 = FLOAT_80436bc8;
  dVar4 = (double)FLOAT_80436bc8;
  *(float *)(param_9 + 0x68) = fVar3;
  fVar1 = FLOAT_80436bc4;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined2 *)(param_9 + 0x72) = 0xf8e4;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x7c) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0x164) = fVar1;
  *(float *)(param_9 + 0x168) = fVar1;
  *(float *)(param_9 + 0x16c) = fVar1;
  *(undefined1 *)(param_9 + 0x170) = 0;
  *(undefined1 *)(param_9 + 0x1a3) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3f0);
  uVar5 = zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),0x18,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe4),0x18,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe8),0x1a,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xec),0x19,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x1a5) = 1;
  *(undefined1 *)(param_9 + 0x1a6) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5813-5821 ==== */
// ==== 80013f3c  zz_0013f3c_ ====

void zz_0013f3c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x1a5) = 0;
  (*(code *)(&PTR_zz_0013f80__802c46d0)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 5825-5837 ==== */
// ==== 80013f80  zz_0013f80_ ====

void zz_0013f80_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80436c5c;
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x164) = fVar1;
  zz_0013fb4_(param_1);
  return;
}
