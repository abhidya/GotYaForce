#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a3e54_(int param_1,uint param_2);
void zz_01a3e98_(int param_1);
void zz_01a4000_(int param_1);
void zz_01a40b0_(int param_1,undefined1 param_2);
void zz_01a41b8_(int param_1);
void zz_01a4244_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_01a4344_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_01a439c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1461-1469 ==== */
// ==== 801a3e54  zz_01a3e54_ ====

void zz_01a3e54_(int param_1,uint param_2)

{
  zz_006660c_(param_1);
  FUN_800669d0(param_1,param_2);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0050.c 1473-1523 ==== */
// ==== 801a3e98  zz_01a3e98_ ====

void zz_01a3e98_(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  undefined4 local_14;
  double local_10;
  
  local_1c = *(float *)(param_1 + 0x38);
  local_18 = FLOAT_8043b594;
  local_14 = *(undefined4 *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),afStack_28);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_1c,afStack_28);
  dVar2 = (double)FLOAT_8043b5a8;
  if ((dVar3 <= dVar2) && (dVar2 = dVar3, dVar3 < (double)FLOAT_8043b598)) {
    dVar2 = (double)FLOAT_8043b598;
  }
  dVar3 = (double)gnt4_acos_bl(dVar2);
  dVar2 = DOUBLE_8043b610;
  if (*(float *)(param_1 + 0x3c) <= FLOAT_8043b594) {
    fVar1 = FLOAT_8043b61c * (float)dVar3;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + 0x222;
    local_10 = __gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
    if (fVar1 < (float)(local_10 - dVar2)) {
      *(short *)(param_1 + 0x18da) = (short)(int)fVar1;
    }
    if (0x3c71 < *(short *)(param_1 + 0x18da)) {
      *(undefined2 *)(param_1 + 0x18da) = 0x3c71;
    }
  }
  else {
    fVar1 = FLOAT_8043b61c * (float)dVar3;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + -0x222;
    fVar1 = -fVar1;
    local_10 = __gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
    if ((float)(local_10 - dVar2) < fVar1) {
      *(short *)(param_1 + 0x18da) = (short)(int)fVar1;
    }
    if (*(short *)(param_1 + 0x18da) < -0x3c71) {
      *(undefined2 *)(param_1 + 0x18da) = 0xc38f;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1527-1558 ==== */
// ==== 801a4000  zz_01a4000_ ====

void zz_01a4000_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  
  fVar2 = FLOAT_8043b598;
  fVar1 = FLOAT_8043b594;
  pfVar4 = (float *)(param_1 + 0x148);
  *(undefined1 *)(param_1 + 0x543) = 1;
  *(float *)(param_1 + 0x148) = fVar2 * *(float *)(param_1 + 0x38);
  *(float *)(param_1 + 0x14c) = fVar1;
  *(float *)(param_1 + 0x150) = fVar2 * *(float *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  *(float *)(param_1 + 0x14c) = FLOAT_8043b620;
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  fVar2 = FLOAT_8043b5a8;
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x38) = FLOAT_8043b594;
  fVar3 = FLOAT_8043b624;
  *(float *)(param_1 + 0x3c) = fVar2;
  fVar2 = FLOAT_8043b628;
  *(float *)(param_1 + 0x40) = fVar1;
  *(float *)(param_1 + 0x44) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x694) = fVar2 + *(float *)(param_1 + 0x1dc8);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1562-1596 ==== */
// ==== 801a40b0  zz_01a40b0_ ====

void zz_01a40b0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,1,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x23;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    *(code **)(puVar1 + 0xc) = zz_01a41b8_;
    *(code **)(puVar1 + 0x10c) = zz_01a44a8_;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    *(undefined4 *)(puVar1 + 0x54) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1600-1616 ==== */
// ==== 801a41b8  zz_01a41b8_ ====

void zz_01a41b8_(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_zz_01a4244__80379318)[*(char *)(param_1 + 0x18)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1620-1663 ==== */
// ==== 801a4244  zz_01a4244_ ====

void zz_01a4244_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x24;
  if (uVar1 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_9 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    iVar3 = *(char *)(param_9 + 0x11) * 0x18;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined *)(param_9 + 0x89) = (&DAT_803792b9)[iVar3];
    uVar4 = *(undefined4 *)(&DAT_803792c0 + iVar3);
    *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803792bc + iVar3);
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803792c4 + iVar3);
    *(code **)(param_9 + 0x100) = zz_01a43f8_;
    uVar5 = zz_0089100_(param_9,1,1);
    zz_01a452c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1667-1686 ==== */
// ==== 801a4344  zz_01a4344_ ====

void zz_01a4344_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  short sVar2;
  
  iVar1 = zz_01a4644_(param_9);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    zz_01a452c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1690-1698 ==== */
// ==== 801a439c  zz_01a439c_ ====

void zz_01a439c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}
