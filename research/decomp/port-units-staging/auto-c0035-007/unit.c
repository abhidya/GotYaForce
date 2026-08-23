#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801336a4(int param_1);
void FUN_801336f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_0133980_(int param_1);
void FUN_80133ae4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_80133b04(int param_1);
void FUN_80133cbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0133df4_(int param_1);
void zz_0133e90_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1914-1922 ==== */
// ==== 801336a4  FUN_801336a4 ====

void FUN_801336a4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80336c18)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1926-2022 ==== */
// ==== 801336f8  FUN_801336f8 ====

void FUN_801336f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x84) = 0;
  *(code **)(param_9 + 0x100) = FUN_80133b04;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  if (*(char *)(param_9 + 0x11) == '\x03') {
    *(undefined1 *)(param_9 + 0x89) = 6;
  }
  else {
    *(undefined1 *)(param_9 + 0x89) = 7;
  }
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  puVar5 = (undefined4 *)(&DAT_80336ba8 + iVar3);
  uVar4 = *puVar5;
  uVar1 = *(undefined4 *)(&DAT_80336bac + iVar3);
  *(undefined4 *)(param_9 + 100) = uVar4;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80336bb0 + iVar3);
  *(int *)(param_9 + 0x174) = param_9 + 0x114;
  *(int *)(param_9 + 0x178) = param_9 + 0x144;
  *(undefined1 *)(param_9 + 0x12) = 2;
  iVar6 = zz_0006f98_(iVar6);
  if (*(char *)(param_9 + 0x11) == 3) {
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe8),(int)sRam80336ba4,
                        iVar6 + 0xc28,uVar4,puVar5,in_r9,in_r10);
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b92 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xec),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xec),extraout_r4_02,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xec));
  }
  else {
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                        (int)*(short *)(&DAT_80336b90 + *(char *)(param_9 + 0x11) * 6),iVar6 + 0xc28
                        ,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe8),
                        (int)*(short *)(&DAT_80336b92 + *(char *)(param_9 + 0x11) * 6),iVar6 + 0xc28
                        ,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xf0),
                        (int)*(short *)(&DAT_80336b94 + *(char *)(param_9 + 0x11) * 6),iVar6 + 0xc28
                        ,uVar4,puVar5,in_r9,in_r10);
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b90 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),extraout_r4,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xe4));
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b92 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xec),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xec),extraout_r4_00,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xec));
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b94 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xf4),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xf4),extraout_r4_01,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xf4));
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0133980_(param_9);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0035.c 2026-2065 ==== */
// ==== 80133980  zz_0133980_ ====

void zz_0133980_(int param_1)

{
  float *pfVar1;
  int iVar2;
  float afStack_28 [4];
  double local_18;
  double local_10;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ('\0' < *(char *)(iVar2 + 0x6e8)) {
    *(char *)(param_1 + 0x12) = *(char *)(iVar2 + 0x6e8);
  }
  if ((*(uint *)(iVar2 + 0x5e0) & 0x20000000) == 0) {
    if ((*(char *)(param_1 + 0x12) == '\x01') && (*(char *)(iVar2 + 0x6e9) == '\x01')) {
      pfVar1 = (float *)(*(char *)(param_1 + 0x11) * 0x18 + -0x7fcc944c);
    }
    else {
      pfVar1 = (float *)(&DAT_80336ba8 + *(char *)(param_1 + 0x11) * 0x18);
    }
    gnt4_PSVECSubtract_bl(pfVar1,(float *)(param_1 + 100),afStack_28);
    gnt4_PSQUATScale_bl((double)FLOAT_80439f0c,afStack_28,afStack_28);
    gnt4_PSVECAdd_bl((float *)(param_1 + 100),afStack_28,(float *)(param_1 + 100));
    if (*(char *)(param_1 + 0x12) == '\x03') {
      local_18 = __gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x17c)) ^ 0x80000000);
      *(short *)(param_1 + 0x17c) =
           (short)(int)-(FLOAT_80439f10 * *(float *)(iVar2 + 0x1dc8) -
                        (float)(local_18 - DOUBLE_80439f18));
    }
    else {
      local_10 = __gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x17c)) ^ 0x80000000);
      *(short *)(param_1 + 0x17c) =
           (short)(int)-(FLOAT_80439f14 * *(float *)(iVar2 + 0x1dc8) -
                        (float)(local_10 - DOUBLE_80439f18));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2069-2077 ==== */
// ==== 80133ae4  FUN_80133ae4 ====

void FUN_80133ae4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0035.c 2081-2133 ==== */
// ==== 80133b04  FUN_80133b04 ====

void FUN_80133b04(int param_1)

{
  int iVar1;
  double dVar2;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  iVar1 = *(int *)(param_1 + 0x90);
  gnt4_PSMTXCopy_bl((float *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    (float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  if (*(char *)(param_1 + 0x11) == '\x03') {
    dVar2 = (double)*(float *)(iVar1 + 0xb4);
    gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,(float *)(param_1 + 0x114));
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(iVar1 + 0x72) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80439f20 *
                                (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_14)) - DOUBLE_80439f18)),
                        afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if (*(char *)(param_1 + 0x12) == '\x01') {
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_1 + 0x17c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80439f20 *
                                (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_14)) - DOUBLE_80439f18)),
                        afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x144));
  }
  if (*(char *)(param_1 + 0x12) == '\x03') {
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_1 + 0x17c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80439f20 *
                                (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_14)) - DOUBLE_80439f18)),
                        afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x144));
    gnt4_PSMTXScale_bl((double)FLOAT_80439f24,(double)FLOAT_80439f28,(double)FLOAT_80439f24,
                       afStack_48);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x144),afStack_48,(float *)(param_1 + 0x144));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2137-2194 ==== */
// ==== 80133cbc  FUN_80133cbc ====

void FUN_80133cbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  cVar1 = *(char *)(param_9 + 0x12);
  iVar4 = *(int *)(param_9 + 0x90);
  if (cVar1 != '\0') {
    cVar2 = *(char *)(param_9 + 0x11);
    if (((cVar2 != '\x02') && (cVar2 != '\x03')) || (*(char *)(iVar4 + 0x6f6) != '\0')) {
      iVar5 = 1;
      if (cVar1 == '\x01') {
        iVar5 = 2;
      }
      if (cVar1 == '\x03') {
        iVar5 = 2;
      }
      if (cVar2 == '\x03') {
        iVar5 = 1;
      }
      iVar9 = param_9 + 0x144;
      iVar6 = 0;
      iVar8 = 0;
      while( true ) {
        if (iVar5 <= iVar6) break;
        iVar7 = 1;
        if ((*(char *)(iVar4 + 0xae) == '\0') && (*(char *)(iVar4 + 0x3ec) != '\x04')) {
          iVar7 = 0;
        }
        iVar3 = *(int *)(param_9 +
                        (iVar7 + (char)(&DAT_804345d0)[*(char *)(param_9 + 0x12) * 2 + iVar6]) * 4 +
                        0xe0);
        zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                    *(float **)(iVar9 + 0x30),param_11,param_12,param_13,param_14,param_15,param_16)
        ;
        param_1 = zz_00097b4_(iVar3,(int)(char)(&DAT_80336c08)
                                               [iVar7 + iVar8 + *(char *)(param_9 + 0x12) * 4]);
        iVar9 = iVar9 + 4;
        iVar8 = iVar8 + 2;
        iVar6 = iVar6 + 1;
      }
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2198-2219 ==== */
// ==== 80133df4  zz_0133df4_ ====

void zz_0133df4_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xc0);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e3758_(param_1,-0x7fcc93d8,2,puVar3 + 3,(float *)(puVar3 + 0x12));
    zz_00e3758_(param_1,-0x7fcc9378,3,puVar3 + 9,(float *)(puVar3 + 0x18));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 2223-2247 ==== */
// ==== 80133e90  zz_0133e90_ ====

void zz_0133e90_(int param_1)

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
      zz_00e38a4_(param_1,(float *)&DAT_80336c28,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12));
      zz_00e38a4_(param_1,(float *)&DAT_80336c88,3,(float *)(puVar2 + 9),(float *)(puVar2 + 0x18));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcc93d8,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
      FUN_800e4f9c(param_1,-0x7fcc9378,3,(float *)(puVar2 + 9),(float *)(puVar2 + 0x27));
    }
  }
  return;
}
