#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a2cfc_(int param_1);
void zz_01a2d4c_(int param_1);
void zz_01a2e08_(int param_1);
void zz_01a2ebc_(int param_1);
void zz_01a30fc_(int param_1);
void zz_01a31a0_(int param_1);
void zz_01a31d8_(int param_1);
void zz_01a324c_(undefined8 param_1,double param_2,double param_3,int param_4);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 801-811 ==== */
// ==== 801a2cfc  zz_01a2cfc_ ====

void zz_01a2cfc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a2d4c__80378780)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 815-837 ==== */
// ==== 801a2d4c  zz_01a2d4c_ ====

void zz_01a2d4c_(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x870),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043b598;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5ac;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 841-870 ==== */
// ==== 801a2e08  zz_01a2e08_ ====

void zz_01a2e08_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d144_(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801a2e7c;
  }
  fVar2 = FLOAT_8043b5d8;
  fVar1 = FLOAT_8043b590;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801a2e7c:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 874-953 ==== */
// ==== 801a2ebc  zz_01a2ebc_ ====

/* WARNING: Removing unreachable block (ram,0x801a30e0) */
/* WARNING: Removing unreachable block (ram,0x801a2ecc) */

void zz_01a2ebc_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar5 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043b594;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b5f0 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043b590
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar4 + 0x8e0);
    local_28 = *(float *)(iVar4 + 0x8f0);
    local_24 = *(undefined4 *)(iVar4 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043b590 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043b594;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043b5e0;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043b5e4;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043b5e0);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar3 = FUN_80066838((double)FLOAT_8043b5ac,param_1);
  if ((int)uVar3 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043b5e8 * (double)*(float *)(param_1 + 0x44)) goto LAB_801a30d4;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar2 = FLOAT_8043b594;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      return;
    }
  }
LAB_801a30d4:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 957-981 ==== */
// ==== 801a30fc  zz_01a30fc_ ====

void zz_01a30fc_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b594;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b594) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b594;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b590 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 985-992 ==== */
// ==== 801a31a0  zz_01a31a0_ ====

void zz_01a31a0_(int param_1)

{
  (**(code **)(&DAT_80435758 + *(char *)(param_1 + 0x581) * 4))();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 996-1009 ==== */
// ==== 801a31d8  zz_01a31d8_ ====

void zz_01a31d8_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a324c__80378790)[*(char *)(param_1 + 0x540)])(param_1);
  if (FLOAT_8043b590 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = FLOAT_8043b590;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1013-1086 ==== */
// ==== 801a324c  zz_01a324c_ ====

/* WARNING: Removing unreachable block (ram,0x801a3450) */
/* WARNING: Removing unreachable block (ram,0x801a325c) */

void zz_01a324c_(undefined8 param_1,double param_2,double param_3,int param_4)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double in_f31;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  fVar1 = FLOAT_8043b5ac;
  *(char *)(param_4 + 0x540) = *(char *)(param_4 + 0x540) + '\x01';
  *(undefined1 *)(param_4 + 0x541) = 0;
  *(float *)(param_4 + 0x558) = fVar1;
  *(undefined1 *)(param_4 + 0x545) = 0;
  if (((*(int *)(param_4 + 0xcc) == 0) || ('\0' < *(char *)(param_4 + 0x1dc))) ||
     (*(char *)(*(int *)(param_4 + 0xcc) + 0x83) != '\0')) {
    *(undefined1 *)(param_4 + 0x541) = 1;
    *(undefined4 *)(param_4 + 0xcc) = 0;
  }
  dVar3 = (double)FLOAT_8043b5f4;
  if ((*(char *)(param_4 + 0x541) == '\0') &&
     (*(char *)(param_4 + 0x88) == *(char *)(*(int *)(param_4 + 0xcc) + 0x88))) {
    local_2c = *(float *)(param_4 + 0x8e0);
    local_28 = *(float *)(param_4 + 0x8f0);
    in_f31 = (double)(FLOAT_8043b5f8 + local_28);
    local_24 = *(undefined4 *)(param_4 + 0x900);
    local_38 = *(float *)(param_4 + 0x518);
    local_34 = *(undefined4 *)(param_4 + 0x51c);
    local_30 = *(undefined4 *)(param_4 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    dVar3 = gnt4_PSVECMag_bl(&local_2c);
    param_2 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x8f0);
    param_3 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x668);
  }
  if ((((double)FLOAT_8043b5fc <= dVar3) ||
      (in_f31 < (double)(float)(param_2 - (double)FLOAT_8043b5f8))) ||
     ((double)(float)(param_2 + param_3) < in_f31)) {
    zz_004beb8_((double)FLOAT_8043b598,param_4,0xf,4,0,0xffffffff,0xffffffff);
    *(float *)(param_4 + 0x80c) = FLOAT_8043b594;
    *(undefined1 *)(param_4 + 0x544) = 0;
  }
  else {
    if (*(char *)(param_4 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_8043b598,param_4,0xf,4,2,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_8043b598,param_4,0xf,4,5,0xffffffff,0xffffffff);
    }
    *(undefined1 *)(param_4 + 0x544) = 1;
  }
  zz_01a3e54_(param_4,0xc0);
  fVar1 = FLOAT_8043b594;
  *(float *)(param_4 + 0x38) = FLOAT_8043b594;
  *(float *)(param_4 + 0x3c) = fVar1;
  *(float *)(param_4 + 0x40) = fVar1;
  iVar2 = zz_006dbe0_(param_4,2,1,1);
  if (iVar2 == 0) {
    *(undefined2 *)(param_4 + 0x548) = 0;
  }
  else {
    *(undefined2 *)(param_4 + 0x548) = 1;
  }
  return;
}
