#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800bbbc0(int param_1);
void FUN_800bbc90(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800bbd38(int param_1);
void FUN_800bbd80(int param_1);
void FUN_800bbde8(int param_1);
void FUN_800bbee8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800bbff0(int param_1);
void FUN_800bc070(int param_1,int param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 961-989 ==== */
// ==== 800bbbc0  FUN_800bbbc0 ====

void FUN_800bbbc0(int param_1)

{
  float fVar1;
  
  zz_006d0dc_(param_1,0xc1,0);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043852c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (fVar1 < *(float *)(param_1 + 0x558)) {
    gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    zz_00b22f4_(param_1);
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 993-1023 ==== */
// ==== 800bbc90  FUN_800bbc90 ====

void FUN_800bbc90(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  zz_004cd24_(param_9,1);
  if (((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) || (*(char *)(param_9 + 0x6eb) < '\x01')) {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if (iVar1 != 0) {
      FUN_800bc2d8(param_9);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1027-1035 ==== */
// ==== 800bbd38  FUN_800bbd38 ====

void FUN_800bbd38(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80301920)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1039-1054 ==== */
// ==== 800bbd80  FUN_800bbd80 ====

void FUN_800bbd80(int param_1)

{
  double dVar1;
  
  FUN_800bbff0(param_1);
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80438534;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043852c;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1058-1098 ==== */
// ==== 800bbde8  FUN_800bbde8 ====

/* WARNING: Removing unreachable block (ram,0x800bbecc) */
/* WARNING: Removing unreachable block (ram,0x800bbdf8) */

void FUN_800bbde8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043852c;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043852c;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bc428(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  else {
    FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
    zz_00679d0_(param_1);
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1102-1149 ==== */
// ==== 800bbee8  FUN_800bbee8 ====

void FUN_800bbee8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  fVar1 = FLOAT_8043852c;
  if (((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) && (*(char *)(param_9 + 0x5db) != '\a')) {
    *(float *)(param_9 + 0x4c) = FLOAT_8043852c;
    *(float *)(param_9 + 0x44) = fVar1;
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_8043852c) {
    if (((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) && ('\0' < *(char *)(param_9 + 0x6eb))) {
      param_11 = 1;
      param_12 = 0;
      iVar2 = zz_006dbe0_(param_9,0,1,0);
      if (iVar2 != 0) {
        FUN_800bc2d8(param_9);
        return;
      }
      goto LAB_800bbfbc;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    if (*(char *)(param_9 + 0x5db) == '\a') {
      param_11 = 0;
      dVar3 = (double)zz_006d0dc_(param_9,0x81,0);
    }
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800bbfbc:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1153-1172 ==== */
// ==== 800bbff0  FUN_800bbff0 ====

void FUN_800bbff0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80438538;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x6eb) = 3;
  if (*(short *)(param_1 + 1000) == 0x20e) {
    *(float *)(param_1 + 0x558) = FLOAT_8043853c;
    *(undefined1 *)(param_1 + 0x6eb) = 4;
  }
  (*(code *)(&PTR_FUN_8030192c)[*(char *)(param_1 + 0x581)])(param_1,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1176-1186 ==== */
// ==== 800bc070  FUN_800bc070 ====

void FUN_800bc070(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80438540,param_1,1,2,param_2,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    zz_004beb8_((double)FLOAT_80438540,param_1,2,0,0,0xffffffff,0xffffffff);
  }
  return;
}
