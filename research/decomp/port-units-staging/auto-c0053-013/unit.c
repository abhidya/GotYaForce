#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01b98ec_(int param_1);
void FUN_801b9ab0(int param_1);
void FUN_801b9abc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_801b9adc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_01b9b1c_(int param_1);
void zz_01b9b68_(int param_1);
int zz_01b9be0_(int param_1,uint param_2);
void zz_01b9df0_(int param_1,int param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3361-3420 ==== */
// ==== 801b98ec  zz_01b98ec_ ====

/* WARNING: Removing unreachable block (ram,0x801b9a8c) */
/* WARNING: Removing unreachable block (ram,0x801b98fc) */

void zz_01b98ec_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  double dVar6;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  if (*(char *)(param_1 + 0x1a) == '\0') {
    *(undefined1 *)(param_1 + 0x1a) = 1;
    fVar1 = FLOAT_8043ba74;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(float *)(param_1 + 0xd8) = fVar1;
    zz_0089444_(param_1);
    *(undefined1 *)(param_1 + 0x98) = 5;
    *(code **)(param_1 + 0x100) = zz_0048288_;
    zz_0089100_(param_1,0,1);
  }
  iVar2 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x48;
  iVar4 = *(int *)(param_1 + 0x90);
  dVar6 = (double)(*(float *)(param_1 + 0xd8) / FLOAT_8043ba74);
  iVar3 = iVar4 + *(short *)(&DAT_8038245e + iVar2) * 0x30;
  local_38 = *(float *)(iVar3 + 0x8dc);
  local_34 = *(undefined4 *)(iVar3 + 0x8ec);
  local_30 = *(undefined4 *)(iVar3 + 0x8fc);
  zz_0046588_(dVar6,(float *)(param_1 + 0x144),&local_38,(float *)(param_1 + 0x38));
  iVar3 = iVar4 + *(short *)(&DAT_8038245e + iVar2) * 0x30;
  local_38 = *(float *)(iVar3 + 0x8d8);
  local_34 = *(undefined4 *)(iVar3 + 0x8e8);
  local_30 = *(undefined4 *)(iVar3 + 0x8f8);
  zz_0046588_(dVar6,(float *)(param_1 + 0x150),&local_38,(float *)(param_1 + 0x9c));
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar4 + *(short *)(&DAT_8038245e + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fc7dba0),&local_38);
  zz_0046588_(dVar6,(float *)(param_1 + 0x15c),&local_38,(float *)(param_1 + 0x20));
  fVar1 = *(float *)(param_1 + 0xd8) - *(float *)(iVar4 + 0x1dc8);
  bVar5 = FLOAT_8043ba5c <= fVar1;
  *(float *)(param_1 + 0xd8) = fVar1;
  if (bVar5) {
    if ((*(char *)(param_1 + 0x1b) == '\0') && (*(float *)(param_1 + 0xd8) <= FLOAT_8043ba78)) {
      zz_00f036c_(param_1,0xdc);
      *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
    }
  }
  else {
    *(undefined1 *)(iVar4 + 0x150) = 1;
    zz_01b9b68_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3424-3431 ==== */
// ==== 801b9ab0  FUN_801b9ab0 ====

void FUN_801b9ab0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3435-3443 ==== */
// ==== 801b9abc  FUN_801b9abc ====

void FUN_801b9abc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3447-3460 ==== */
// ==== 801b9adc  FUN_801b9adc ====

void FUN_801b9adc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3464-3474 ==== */
// ==== 801b9b1c  zz_01b9b1c_ ====

void zz_01b9b1c_(int param_1)

{
  zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),0);
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3478-3494 ==== */
// ==== 801b9b68  zz_01b9b68_ ====

void zz_01b9b68_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((*(short *)(iVar1 + 1000) == 0x407) && (*(char *)(iVar1 + 0x150) == '\x01')) {
    zz_006de10_(iVar1,2);
    *(undefined1 *)(iVar1 + 0x150) = 0;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3498-3557 ==== */
// ==== 801b9be0  zz_01b9be0_ ====

int zz_01b9be0_(int param_1,uint param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_30;
  float local_2c;
  float local_28;
  float afStack_24 [7];
  
  iVar3 = *(int *)(param_1 + 200);
  fVar1 = FLOAT_8043ba5c;
  if (iVar3 != 0) {
    iVar2 = (param_2 & 0x7f) * 0x48;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + *(short *)(&DAT_8038245e + iVar2) * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fc7dba0),afStack_24);
    local_30 = *(float *)(iVar3 + 100);
    local_2c = *(float *)(iVar3 + 0x68);
    local_28 = *(float *)(iVar3 + 0x6c);
    gnt4_PSVECSubtract_bl(&local_30,afStack_24,&local_30);
    dVar5 = (double)(local_30 * local_30 + local_28 * local_28);
    if ((double)FLOAT_8043ba5c < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar5 = (double)(float)(dVar5 * DOUBLE_8043ba80 * dVar4 *
                                      -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88));
    }
    local_30 = (float)dVar5;
    if (dVar5 < (double)FLOAT_8043ba90) {
      local_30 = FLOAT_8043ba90;
    }
    fVar1 = (*(float *)(&DAT_8038246c + iVar2) * local_30 * local_30) /
            (FLOAT_8043ba60 * *(float *)(&DAT_80382450 + iVar2) * *(float *)(&DAT_80382450 + iVar2))
    ;
    dVar5 = (double)(local_30 * local_30 - FLOAT_8043ba94 * fVar1 * (fVar1 + local_2c));
    if (dVar5 < (double)FLOAT_8043ba5c) {
      dVar5 = (double)FLOAT_8043ba5c;
    }
    if ((double)FLOAT_8043ba5c < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar5 = (double)(float)(dVar5 * DOUBLE_8043ba80 * dVar4 *
                                      -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88));
    }
    dVar5 = gnt4_atan((double)((float)((double)local_30 - dVar5) / (FLOAT_8043ba60 * fVar1)));
    fVar1 = (float)dVar5;
    if (FLOAT_8043ba98 <= fVar1) {
      fVar1 = FLOAT_8043ba98;
    }
  }
  return (int)(short)-(short)(int)(FLOAT_8043ba9c * fVar1);
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3561-3606 ==== */
// ==== 801b9df0  zz_01b9df0_ ====

void zz_01b9df0_(int param_1,int param_2)

{
  byte bVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  bVar1 = *(byte *)(param_1 + 0x11);
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 600;
  fVar2 = FLOAT_8043ba5c;
  if (param_2 == 0) {
    *(float *)(param_1 + 0x38) = FLOAT_8043ba5c;
    *(float *)(param_1 + 0x40) = fVar2;
  }
  else {
    local_18 = *(float *)(param_1 + 0x1cc);
    local_14 = *(undefined4 *)(param_1 + 0x1d0);
    local_10 = *(undefined4 *)(param_1 + 0x1d4);
    gnt4_PSQUATScale_bl((double)FLOAT_8043baa0,&local_18,&local_18);
    dVar4 = gnt4_PSVECMag_bl(&local_18);
    dVar3 = (double)(FLOAT_8043baa4 * *(float *)(param_1 + 0xb4));
    if (dVar3 < dVar4) {
      gnt4_PSQUATScale_bl((double)(float)(dVar3 / dVar4),&local_18,&local_18);
    }
    *(float *)(param_1 + 0x38) = local_18;
    *(undefined4 *)(param_1 + 0x3c) = local_14;
    *(undefined4 *)(param_1 + 0x40) = local_10;
  }
  if (FLOAT_8043ba5c < *(float *)(param_1 + 0x3c)) {
    *(float *)(param_1 + 0x3c) = FLOAT_8043ba5c;
  }
  if (*(float *)(param_1 + 0x50) <
      FLOAT_8043ba60 * *(float *)(&DAT_8038246c + (bVar1 & 0x7f) * 0x48)) {
    *(float *)(param_1 + 0x50) = FLOAT_8043ba60 * *(float *)(&DAT_8038246c + (bVar1 & 0x7f) * 0x48);
  }
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined2 *)(param_1 + 0x272) = 1;
  return;
}
