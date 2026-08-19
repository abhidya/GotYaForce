#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
int zz_0006f98_(int param_1);
void zz_0006fb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10,int param_11, undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15, undefined4 param_16);
void zz_0007030_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10,int param_11, int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15, undefined4 param_16);
void zz_00070e4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10,int param_11, int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15, undefined4 param_16);
void zz_0007198_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11 ,int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15, undefined4 param_16);
void zz_000726c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10, float *param_11,uint param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0007338_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10, float *param_11,int param_12,uint param_13,undefined4 param_14,undefined4 param_15, undefined4 param_16);
void zz_000744c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10, float *param_11,int param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1501-1507 ==== */
// ==== 80006f98  zz_0006f98_ ====

int zz_0006f98_(int param_1)

{
  return *(char *)(param_1 + 0x97) * 0xc30 + -0x7fc44b40;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1511-1542 ==== */
// ==== 80006fb4  zz_0006fb4_ ====

void zz_0006fb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  int extraout_r4;
  int iVar3;
  undefined4 *puVar4;
  
  iVar2 = **(int **)(param_9 + 0x10);
  puVar4 = *(undefined4 **)(iVar2 + param_11 * 4);
  iVar3 = param_11;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),iVar2,param_11,param_12,param_13,param_14
                                 ,param_15,param_16);
    iVar2 = extraout_r4;
  }
  piVar1 = gnt4_HSD_JObjLoadJoint
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar4
                      ,iVar2,iVar3,param_12,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar1;
  *(int *)(param_10 + 0x14) = param_11;
  *(undefined1 *)(param_10 + 0xb) = 0;
  *(undefined1 *)(param_10 + 0x10) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1546-1592 ==== */
// ==== 80007030  zz_0007030_ ====

void zz_0007030_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  puVar7 = *(undefined4 **)(**(int **)(param_9 + 0x10) + param_11 * 4);
  iVar5 = param_11;
  iVar6 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  ppuVar1 = zz_02429e4_();
  uVar8 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008da7c__802da7f0,0x802e0000,iVar5,iVar6,param_13,param_14,param_15,
                      param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d714_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar7,
                      uVar4,iVar5,iVar6,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar3;
  zz_024298c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,iVar5,
              iVar6,param_13,param_14,param_15,param_16);
  zz_008d714_(uVar2);
  *(int *)(param_10 + 0x14) = param_11;
  *(undefined1 *)(param_10 + 0xb) = 0;
  *(undefined1 *)(param_10 + 0x10) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1596-1642 ==== */
// ==== 800070e4  zz_00070e4_ ====

void zz_00070e4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  puVar7 = *(undefined4 **)(**(int **)(param_9 + 0x10) + param_11 * 4);
  iVar5 = param_11;
  iVar6 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  ppuVar1 = zz_02429e4_();
  uVar8 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008dae4__802da844,0x802e0000,iVar5,iVar6,param_13,param_14,param_15,
                      param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d780_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar7,
                      uVar4,iVar5,iVar6,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar3;
  zz_024298c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,iVar5,
              iVar6,param_13,param_14,param_15,param_16);
  zz_008d780_(uVar2);
  *(int *)(param_10 + 0x14) = param_11;
  *(undefined1 *)(param_10 + 0xb) = 0;
  *(undefined1 *)(param_10 + 0x10) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1646-1709 ==== */
// ==== 80007198  zz_0007198_ ====

void zz_0007198_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11
                ,int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  
  puVar6 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  pcVar4 = param_11;
  iVar5 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  piVar1 = gnt4_HSD_JObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  *(int **)(param_10 + 0xc) = piVar1;
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar8 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)piVar1,
                       0x10,pcVar4,iVar5,param_13,param_14,param_15,param_16);
    piVar2 = gnt4_HSD_JObjLoadJoint
                       (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar6
                        ,extraout_r4,pcVar4,iVar5,param_13,param_14,param_15,param_16);
    if (piVar2 != (int *)0x0) {
      dVar9 = (double)gnt4_HSD_JObjAddChild
                                (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 (int)piVar1,(int)piVar2,pcVar4,iVar5,param_13,param_14,param_15,
                                 param_16);
      iVar7 = 1;
      uVar3 = extraout_r4_00;
      while ((iVar7 < param_12 &&
             (piVar1 = gnt4_HSD_JObjLoadJoint
                                 (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  (int *)*puVar6,uVar3,pcVar4,iVar5,param_13,param_14,param_15,
                                  param_16), piVar1 != (int *)0x0))) {
        dVar9 = (double)zz_02500b0_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar2,(int)piVar1,pcVar4,iVar5,param_13,param_14,param_15,
                                    param_16);
        iVar7 = iVar7 + 1;
        uVar3 = extraout_r4_01;
        piVar2 = piVar1;
      }
      *(char **)(param_10 + 0x14) = param_11;
      *(undefined1 *)(param_10 + 0xb) = 0;
      *(undefined1 *)(param_10 + 0x10) = 1;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1713-1762 ==== */
// ==== 8000726c  zz_000726c_ ====

void zz_000726c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  int extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  
  iVar2 = **(int **)(param_9 + 0x10);
  puVar5 = *(undefined4 **)(iVar2 + (int)param_11 * 4);
  pfVar3 = param_11;
  uVar4 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),iVar2,param_11,param_12,param_13,param_14
                                 ,param_15,param_16);
    iVar2 = extraout_r4;
  }
  piVar1 = gnt4_HSD_JObjLoadJoint
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar5
                      ,iVar2,pfVar3,uVar4,param_13,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar1;
  if (*(int *)(param_10 + 0xc) != 0) {
    *(float **)(param_10 + 0x14) = param_11;
    *(undefined1 *)(param_10 + 0xb) = 0;
    *(undefined1 *)(param_10 + 0x10) = 1;
    if (PTR_DAT_80433934[0x51] == '\x03') {
      param_12 = 0;
    }
    uVar6 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,param_12 ^ 0x80000000) -
                                       DOUBLE_80436a48),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,param_9,param_10,pfVar3,uVar4,param_13,param_14,param_15,
                        param_16);
    uVar6 = zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                        extraout_r4_00,pfVar3,uVar4,param_13,param_14,param_15,param_16);
    zz_0007d40_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                extraout_r4_01,pfVar3,uVar4,param_13,param_14,param_15,param_16);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1766-1829 ==== */
// ==== 80007338  zz_0007338_ ====

void zz_0007338_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,int param_12,uint param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined **ppuVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined8 uVar9;
  
  puVar8 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  pfVar5 = param_11;
  iVar6 = param_12;
  uVar7 = param_13;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  ppuVar1 = zz_02429e4_();
  uVar9 = zz_024298c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      &PTR_zz_008da7c__802da7f0,0x802e0000,pfVar5,iVar6,uVar7,param_14,param_15,
                      param_16);
  if (param_12 == 0) {
    param_12 = param_10 + 0x18;
  }
  uVar4 = extraout_r4;
  uVar2 = zz_008d714_(param_12);
  piVar3 = gnt4_HSD_JObjLoadJoint
                     (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar8,
                      uVar4,pfVar5,iVar6,uVar7,param_14,param_15,param_16);
  *(int **)(param_10 + 0xc) = piVar3;
  if (*(int *)(param_10 + 0xc) != 0) {
    zz_024298c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppuVar1,uVar4,pfVar5,
                iVar6,uVar7,param_14,param_15,param_16);
    zz_008d714_(uVar2);
    *(float **)(param_10 + 0x14) = param_11;
    *(undefined1 *)(param_10 + 0xb) = 0;
    *(undefined1 *)(param_10 + 0x10) = 1;
    if (PTR_DAT_80433934[0x51] == '\x03') {
      param_13 = 0;
    }
    uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,param_13 ^ 0x80000000) -
                                       DOUBLE_80436a48),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,param_9,param_10,pfVar5,iVar6,uVar7,param_14,param_15,
                        param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                        extraout_r4_00,pfVar5,iVar6,uVar7,param_14,param_15,param_16);
    zz_0007d40_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                extraout_r4_01,pfVar5,iVar6,uVar7,param_14,param_15,param_16);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 1833-1917 ==== */
// ==== 8000744c  zz_000744c_ ====

void zz_000744c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  undefined4 extraout_r4_02;
  float *pfVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  double dVar9;
  
  puVar7 = *(undefined4 **)(**(int **)(param_9 + 0x10) + (int)param_11 * 4);
  pfVar4 = param_11;
  iVar5 = param_12;
  if (*(int **)(param_10 + 0xc) != (int *)0x0) {
    param_1 = gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int **)(param_10 + 0xc),**(int **)(param_9 + 0x10),param_11,
                                 param_12,param_13,param_14,param_15,param_16);
  }
  piVar1 = gnt4_HSD_JObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  *(int **)(param_10 + 0xc) = piVar1;
  if (*(int *)(param_10 + 0xc) != 0) {
    uVar8 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)piVar1,
                       0x10,(undefined *)pfVar4,iVar5,param_13,param_14,param_15,param_16);
    piVar2 = gnt4_HSD_JObjLoadJoint
                       (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)*puVar7
                        ,extraout_r4,pfVar4,iVar5,param_13,param_14,param_15,param_16);
    if (piVar2 != (int *)0x0) {
      if ((undefined4 *)puVar7[2] != (undefined4 *)0x0) {
        pfVar4 = *(float **)puVar7[2];
        iVar5 = 0;
        gnt4_HSD_JObjAddAnimAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,0,pfVar4,
                   (undefined4 *)0x0,param_13,param_14,param_15,param_16);
        uVar8 = gnt4_HSD_JObjReqAnimAll();
      }
      dVar9 = (double)gnt4_HSD_JObjAddChild
                                (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 (int)piVar1,(int)piVar2,(char *)pfVar4,iVar5,param_13,param_14,
                                 param_15,param_16);
      uVar3 = extraout_r4_00;
      for (iVar6 = 1; iVar6 < param_12; iVar6 = iVar6 + 1) {
        piVar1 = gnt4_HSD_JObjLoadJoint
                           (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar7,uVar3,pfVar4,iVar5,param_13,param_14,param_15,param_16);
        if (piVar1 == (int *)0x0) {
          return;
        }
        if ((undefined4 *)puVar7[2] != (undefined4 *)0x0) {
          pfVar4 = *(float **)puVar7[2];
          iVar5 = 0;
          gnt4_HSD_JObjAddAnimAll
                    (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar1,0,pfVar4,
                     (undefined4 *)0x0,param_13,param_14,param_15,param_16);
          dVar9 = (double)gnt4_HSD_JObjReqAnimAll();
        }
        dVar9 = (double)zz_02500b0_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)piVar2,(int)piVar1,pfVar4,iVar5,param_13,param_14,param_15,
                                    param_16);
        uVar3 = extraout_r4_01;
        piVar2 = piVar1;
      }
      uVar8 = zz_0007c30_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                          uVar3,pfVar4,iVar5,param_13,param_14,param_15,param_16);
      zz_0007d40_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                  extraout_r4_02,pfVar4,iVar5,param_13,param_14,param_15,param_16);
      *(float **)(param_10 + 0x14) = param_11;
      *(undefined1 *)(param_10 + 0xb) = 0;
      *(undefined1 *)(param_10 + 0x10) = 1;
    }
  }
  return;
}
