#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8007bb34(int param_1);
void FUN_8007bb6c(int param_1);
void FUN_8007bbe0(undefined8 param_1,double param_2,double param_3,int param_4);
void FUN_8007be08(int param_1);
void FUN_8007bf70(int param_1);
void FUN_8007c19c(int param_1);
void FUN_8007c350(int param_1);
void FUN_8007c414(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2927-2934 ==== */
// ==== 8007bb34  FUN_8007bb34 ====

void FUN_8007bb34(int param_1)

{
  (*(code *)(&PTR_FUN_804338d8)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2938-2951 ==== */
// ==== 8007bb6c  FUN_8007bb6c ====

void FUN_8007bb6c(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6668)[*(char *)(param_1 + 0x540)])(param_1);
  if (FLOAT_804378ec < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = FLOAT_804378ec;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2955-3029 ==== */
// ==== 8007bbe0  FUN_8007bbe0 ====

/* WARNING: Removing unreachable block (ram,0x8007bdec) */
/* WARNING: Removing unreachable block (ram,0x8007bbf0) */

void FUN_8007bbe0(undefined8 param_1,double param_2,double param_3,int param_4)

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
  
  fVar1 = FLOAT_80437904;
  *(char *)(param_4 + 0x540) = *(char *)(param_4 + 0x540) + '\x01';
  *(undefined1 *)(param_4 + 0x541) = 0;
  *(float *)(param_4 + 0x558) = fVar1;
  *(undefined1 *)(param_4 + 0x545) = 0;
  if (((*(int *)(param_4 + 0xcc) == 0) || ('\0' < *(char *)(param_4 + 0x1dc))) ||
     (*(char *)(*(int *)(param_4 + 0xcc) + 0x83) != '\0')) {
    *(undefined1 *)(param_4 + 0x541) = 1;
    *(undefined4 *)(param_4 + 0xcc) = 0;
  }
  dVar3 = (double)FLOAT_8043794c;
  if ((*(char *)(param_4 + 0x541) == '\0') &&
     (*(char *)(param_4 + 0x88) == *(char *)(*(int *)(param_4 + 0xcc) + 0x88))) {
    local_2c = *(float *)(param_4 + 0x8e0);
    local_28 = *(float *)(param_4 + 0x8f0);
    in_f31 = (double)(FLOAT_80437950 + local_28);
    local_24 = *(undefined4 *)(param_4 + 0x900);
    local_38 = *(float *)(param_4 + 0x518);
    local_34 = *(undefined4 *)(param_4 + 0x51c);
    local_30 = *(undefined4 *)(param_4 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    dVar3 = gnt4_PSVECMag_bl(&local_2c);
    param_2 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x8f0);
    param_3 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x668);
  }
  if ((((double)FLOAT_80437954 <= dVar3) ||
      (in_f31 < (double)(float)(param_2 - (double)FLOAT_80437950))) ||
     ((double)(float)(param_2 + param_3) < in_f31)) {
    zz_004beb8_((double)FLOAT_804378f0,param_4,0xf,4,0,0xffffffff,0xffffffff);
    *(float *)(param_4 + 0x80c) = FLOAT_804378e8;
    *(undefined1 *)(param_4 + 0x544) = 0;
  }
  else {
    if (*(char *)(param_4 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_804378f0,param_4,0xf,4,2,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804378f0,param_4,0xf,4,5,0xffffffff,0xffffffff);
    }
    *(undefined1 *)(param_4 + 0x544) = 1;
  }
  zz_007c800_(param_4,0xc0);
  fVar1 = FLOAT_804378e8;
  *(float *)(param_4 + 0x38) = FLOAT_804378e8;
  *(float *)(param_4 + 0x3c) = fVar1;
  *(float *)(param_4 + 0x40) = fVar1;
  iVar2 = zz_006dbe0_(param_4,2,1,1);
  if (iVar2 == 0) {
    *(undefined2 *)(param_4 + 0x548) = 0;
    *(undefined1 *)(param_4 + 0x6e8) = 8;
  }
  else {
    *(undefined2 *)(param_4 + 0x548) = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3033-3086 ==== */
// ==== 8007be08  FUN_8007be08 ====

void FUN_8007be08(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_007c800_(param_1,0xc0), iVar3 != 0)) {
    if ((*(int *)(param_1 + 0xcc) != 0) &&
       (*(char *)(param_1 + 0x88) != *(char *)(*(int *)(param_1 + 0xcc) + 0x88))) {
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
    }
    FUN_80066958(param_1);
    fVar2 = FLOAT_804378f8;
    fVar1 = FLOAT_804378ec;
    if (*(char *)(param_1 + 0x544) == '\x01') {
      if (*(short *)(param_1 + 0x548) == 0) {
        if (*(char *)(param_1 + 0x581) == '\0') {
          *(undefined1 *)(param_1 + 0x73f) = 0;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
          zz_006a474_(param_1);
          return;
        }
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar2 = FLOAT_80437900;
      *(float *)(param_1 + 0x558) = fVar1;
      fVar1 = FLOAT_804378e8;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(float *)(param_1 + 0x50) = fVar1;
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(undefined1 *)(param_1 + 0x144) = 1;
    }
    if (FLOAT_8043790c < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3090-3161 ==== */
// ==== 8007bf70  FUN_8007bf70 ====

void FUN_8007bf70(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x144) == '\x01') {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x8dc);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x8ec);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x8fc);
  }
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804378ec;
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(short *)(param_1 + 0x548) == 0) {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\t')) {
        *(undefined1 *)(param_1 + 0x6e8) = 8;
        *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
    }
    else {
      zz_007c800_(param_1,0xc0);
      if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
        FUN_8006c1c8((double)FLOAT_8043791c,param_1,(float *)(param_1 + 0x518));
        if (FLOAT_80437930 <= *(float *)(param_1 + 0x760)) {
          *(float *)(param_1 + 0x4c) = FLOAT_804378f8;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_80437958;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
      FUN_80067610(param_1);
      if ((*(float *)(param_1 + 0x4c) < FLOAT_804378e8) &&
         (*(float *)(param_1 + 0x44) < FLOAT_80437900)) {
        *(float *)(param_1 + 0x44) = FLOAT_80437900;
      }
      fVar1 = FLOAT_804378ec;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\n')) {
        *(undefined1 *)(param_1 + 0x6e8) = 2;
        *(undefined1 *)(param_1 + 0x545) = 1;
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        *(undefined1 *)(param_1 + 0x1cf0) = 0;
      }
      else if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        *(undefined1 *)(param_1 + 0x1cf0) = 0;
      }
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_007c9ac_(param_1);
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  if (*(char *)(param_1 + 0x545) == '\x01') {
    zz_00f0104_(param_1,0x1c,1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3165-3221 ==== */
// ==== 8007c19c  FUN_8007c19c ====

void FUN_8007c19c(int param_1)

{
  float fVar1;
  double dVar2;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  zz_00f0104_(param_1,0x1c,1);
  zz_007c800_(param_1,0xc0);
  if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
    local_18 = *(float *)(param_1 + 0x518);
    local_14 = *(float *)(param_1 + 0x51c) - FLOAT_80437950;
    local_10 = *(undefined4 *)(param_1 + 0x520);
    FUN_8006c1c8((double)FLOAT_8043791c,param_1,&local_18);
    if (FLOAT_80437930 <= *(float *)(param_1 + 0x760)) {
      *(float *)(param_1 + 0x4c) = FLOAT_804378f8;
    }
    else {
      *(float *)(param_1 + 0x4c) = FLOAT_80437958;
    }
    zz_007c844_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  FUN_80067610(param_1);
  if (*(float *)(param_1 + 0x4c) < FLOAT_804378e8) {
    if (*(float *)(param_1 + 0x44) < FLOAT_80437900) {
      *(float *)(param_1 + 0x44) = FLOAT_80437900;
    }
  }
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar1 = FLOAT_8043795c;
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(float *)(param_1 + 0x558) <= FLOAT_804378e8) {
      dVar2 = (double)FLOAT_804378f0;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x542) = 0;
      *(undefined1 *)(param_1 + 0x543) = 0;
      *(float *)(param_1 + 0x4c) = fVar1;
      zz_004beb8_(dVar2,param_1,0xf,4,1,0xffffffff,0xffffffff);
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_007c9ac_(param_1);
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0011.c 3225-3248 ==== */
// ==== 8007c350  FUN_8007c350 ====

void FUN_8007c350(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x540) = 7;
  }
  FUN_80067610(param_1);
  if (*(char *)(param_1 + 0x543) == '\x01') {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x148);
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x14c);
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x150);
  }
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                           DOUBLE_80437968) * FLOAT_80437960);
  *(undefined1 *)(param_1 + 0x547) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3252-3272 ==== */
// ==== 8007c414  FUN_8007c414 ====

void FUN_8007c414(int param_1)

{
  float fVar1;
  uint uVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_007c800_(param_1,0xc0);
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar2 = FUN_80066838((double)FLOAT_80437970,param_1), 0 < (int)uVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_004cff4_(param_1,0xf);
  }
  return;
}
